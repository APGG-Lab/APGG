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
        m_punishmentFine = m_punishmentFineBase * nMoralists;

        int nCooperators = counter[Faction::Cooperator] + counter[Faction::Moralist];
        m_payoff = m_synergyFactor * nCooperators / group.size();
    }

    void GroupLevelPayoffCalculator::applyPayoff(Grid& grid, Group & group)
    {
        calculateCosts(group);

        float groupPayoffPool = 0.f; //Group money pool
        float payoff = 0.f; //Individual payoff
        float poolAmount = 0.f; //Amount of individual payoff which goes to the group money pool

        for (const GridIndex index : group.data()) {
            payoff = calculateIndividualPayoff(grid[index]);

            poolAmount = payoff * (1.0f - m_individualism);
            groupPayoffPool += poolAmount;
            grid[index].m_payoff = payoff - poolAmount;
        }

        //Divide groupPayoff by number of group members and apply it to the individual payoff
        float groupPayoffPerMember = groupPayoffPool / static_cast<int>(group.data().size());

        for (const GridIndex index : group.data()) {
            grid[index].m_payoff += groupPayoffPerMember;
        }
    }

    float GroupLevelPayoffCalculator::calculateIndividualPayoff(Organism& organism)
    {
        float payoff = 0;

        if (organism.m_moralist) { //Subtract punishment costs from moralists/immoralists
            payoff -= m_punishmentCost;
        };

        if (!organism.m_cooperated) {//Substract punishment fine from defectors/immoralists
            payoff -= m_punishmentFine;
        }
        else {
            payoff -= m_cooperationCost; //Substract 1 from cooperators / moralists
        }

        if (!m_allowPayoffBelowZero && m_payoff < 0) {
            payoff = 0;
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
