#include "DefaultPayOffCalculator.h"

namespace APGG {


    DefaultPayOffCalculator::DefaultPayOffCalculator(){}

    void DefaultPayOffCalculator::calculateCosts(const int groupSize)
    {
        //Precalculate costs, fines and payoffs

        int nPunished = m_counter[FACTION_DEFECTOR] + m_counter[FACTION_IMMORALIST];
        m_punishmentCost = m_punishmentCostBase * nPunished;

        int nMoralists = m_counter[FACTION_MORALIST] + m_counter[FACTION_IMMORALIST];
        m_punishmentFine = m_punishmentFineBase * nMoralists;

        int nCooperators = m_counter[FACTION_COOPERATOR] + m_counter[FACTION_MORALIST];
        m_payoff = m_synergyFactor * nCooperators / groupSize;
    }

    void DefaultPayOffCalculator::applyPayoff(rOrganism & rorganism)
    {
        auto& organism = rorganism.get();

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

    void DefaultPayOffCalculator::applyPayoff(Group & group)
    {
        for (rOrganism& organism : group.data()) {
            applyPayoff(organism);
        }
    }
}