#include "GroupLevelPayoffCalculator.h"

namespace APGG {


    GroupLevelPayoffCalculator::GroupLevelPayoffCalculator(){}

    void GroupLevelPayoffCalculator::calculateCosts(Group& group)
    {
        std::array<unsigned int, Faction::Count> counter = group.getFactionCounter();

        //Precalculate costs, fines and payoffs

        int nPunished = counter[Faction::Defector] + counter[Faction::Immoralist];
        m_punishmentCost = m_punishmentCostBase * nPunished;

        int nMoralists = counter[Faction::Moralist] + counter[Faction::Immoralist];
        m_punishmentFine = m_punishmentFineBase * nMoralists / group.size();

        int nCooperators = counter[Faction::Cooperator] + counter[Faction::Moralist];
        m_payoff = (nCooperators / group.size()) * (m_synergyFactor + m_individualism - 1.f);
    }

    void GroupLevelPayoffCalculator::applyPayoff(Grid& grid, Group & group)
    {
        calculateCosts(group);

        for (const GridIndex index : group.data()) {
            grid[index].m_payoff = calculateIndividualPayoff(grid[index]);
        }
    }

    float GroupLevelPayoffCalculator::calculateIndividualPayoff(Organism& organism)
    {
        float payoff = 0.f;

        if (organism.m_moralist) { //Subtract punishment costs from moralists/immoralists
            payoff -= m_punishmentCost;
        };

        if (!organism.m_cooperated) {
            payoff += m_payoff - m_punishmentFine;
        }
        else {
            payoff += m_payoff - m_individualism - (1.f - m_individualism) * m_punishmentFine;
        }

        if (!m_allowPayoffBelowZero && m_payoff < 0.f) {
            payoff = 0.f;
        }

        return payoff;
    }

	void GroupLevelPayoffCalculator::configure(Config& config)
	{
		m_cooperationCost = std::stof(config.getValue("cooperateCost"));
		m_synergyFactor = std::stof(config.getValue("synergyFactor"));
		m_punishmentCostBase = std::stof(config.getValue("punishmentCost"));
		m_punishmentFineBase = std::stof(config.getValue("punishmentFine"));
        m_individualism = std::stof(config.getValue("payoffIndividualism"));
	}
}
