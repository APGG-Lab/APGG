#include "AsymmetricPayoffCalculator.h"

namespace APGG {


    AsymmetricPayoffCalculator ::AsymmetricPayoffCalculator (){}

    void AsymmetricPayoffCalculator ::calculateCosts(Group& group)
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

    void AsymmetricPayoffCalculator ::applyPayoff(Grid& grid, Group & group)
    {
        calculateCosts(group);

        float groupPayoffPool = 0.f; //Group money pool

        for (const GridIndex index : group.data()) {
            float payoff = calculateIndividualPayoff(grid[index]);

            if (payoff > 0) { //only add positive numbers to the pool
                groupPayoffPool += payoff;
            }
        }

        for (unsigned int i = 0; i < group.size(); i++) {
           // const unsigned int numerator = m_groupRanks[i];
            const unsigned int numerator = i + 1; //In case ranks are not bound to the position (Focal can be any rank) use this
            const float share = groupPayoffPool * (numerator / m_denominator);
            const GridIndex index = group[i];

            grid[index].m_payoff += share;

            //It would be cool to have the following part in an extra for loop,
            //but that will cost us cpu time. So we will use this loop instead
            if (!m_allowPayoffBelowZero && grid[index].m_payoff < 0) {
                grid[index].m_payoff = 0;
            }
        }



    }

    float AsymmetricPayoffCalculator ::calculateIndividualPayoff(Organism& organism)
    {
        float payoff = m_payoff;

        if (organism.m_moralist) { //Subtract punishment costs from moralists/immoralists
            payoff -= m_punishmentCost;
        };

        if (!organism.m_cooperator) {//Substract punishment fine from defectors/immoralists
            payoff -= m_punishmentFine;
        }
        else {
            payoff -= m_cooperationCost; //Substract 1 from cooperators / moralists
        }

        return payoff;
    }

	void AsymmetricPayoffCalculator ::configure(Config& config)
	{
		m_cooperationCost = std::stof(config.getValue("cooperateCost"));
		m_synergyFactor = std::stof(config.getValue("synergyFactor"));
		m_punishmentCostBase = std::stof(config.getValue("punishmentCost"));
		m_punishmentFineBase = std::stof(config.getValue("punishmentFine"));

        const unsigned int groupSize = std::stoul(config.getValue("groupSize"));
        m_denominator = ((groupSize * groupSize) + groupSize) / 2.0f; //(n^2 + n) / 2 => (5*5) + 5/2
	}
}
