#include "AsymmetricPayoffCalculator.h"

namespace APGG {


    AsymmetricPayOffCalculator::AsymmetricPayOffCalculator(){}

    void AsymmetricPayOffCalculator::calculateCosts(Group& group)
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


    void AsymmetricPayOffCalculator::applyPayoff(Grid& grid, Group & group)
    {
        calculateCosts(group);

        for (const GridIndex index : group.data()) {
            grid[index].m_payoff += calculateIndividualPayoff(grid[index]);

            if (!m_allowPayoffBelowZero && grid[index].m_payoff < 0) {
                grid[index].m_payoff = 0;
            }
        }
    }

	void AsymmetricPayOffCalculator::configure(Config& config)
	{
		m_cooperationCost = std::stof(config.getValue("cooperateCost"));
		m_synergyFactor = std::stof(config.getValue("synergyFactor"));
		m_punishmentCostBase = std::stof(config.getValue("punishmentCost"));
		m_punishmentFineBase = std::stof(config.getValue("punishmentFine"));
	}

	float AsymmetricPayOffCalculator::calculateIndividualPayoff(Organism& organism)
	{

        float payoff = m_payoff;

        if (organism.m_moralist) { //Subtract punishment costs from moralists/immoralists
            payoff -= m_punishmentCost;
        };

        if (!organism.m_cooperated) {//Substract punishment fine from defectors/immoralists
            payoff -= m_punishmentFine;
        }
        else {
            payoff -= m_cooperationCost; //Substract 1 from cooperators / moralists
        }

        return payoff;
	}
    uint8_t AsymmetricPayOffCalculator::getGenomeNumber() const
    {
        return 3;
    }
}
