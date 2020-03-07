#include "DefaultPayoffCalculator.h"

namespace APGG {


    DefaultPayOffCalculator::DefaultPayOffCalculator(){}

    void DefaultPayOffCalculator::calculateCosts(Group& group)
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

    void DefaultPayOffCalculator::applyPayoff(Organism & organism)
    {

        organism.m_payoff += m_payoff;

        if (organism.m_moralist) { //Subtract punishment costs from moralists/immoralists
            organism.m_payoff -= m_punishmentCost;
        };

        if (!organism.m_cooperated) {//Substract punishment fine from defectors/immoralists
            organism.m_payoff -= m_punishmentFine;
        }
        else {
            organism.m_payoff -= m_cooperationCost; //Substract 1 from cooperators / moralists
        }

        if (!m_allowPayoffBelowZero && organism.m_payoff < 0) {
            organism.m_payoff = 0;
        }
    }

    void DefaultPayOffCalculator::applyPayoff(Grid& grid, Group & group)
    {
        calculateCosts(group);

        for (const unsigned int& index : group.data()) {
            applyPayoff(grid[index]);
        }
    }
	void DefaultPayOffCalculator::configure(Config& config)
	{
		m_cooperationCost = std::stof(config.getValue("cooperateCost"));
		m_synergyFactor = std::stof(config.getValue("synergyFactor"));
		m_punishmentCostBase = std::stof(config.getValue("punishmentCost"));
		m_punishmentFineBase = std::stof(config.getValue("punishmentFine"));
	}
}
