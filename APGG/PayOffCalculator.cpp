#include "PayOffCalculator.h"



PayOffCalculator::PayOffCalculator() : m_synergyFactor(1), m_punishmentCostBase(1.0f), m_punishmentFineBase(1.0f), m_allowPayoffBelowZero(true)
{
}

void PayOffCalculator::setSynergyFactor(const float factor)
{
    m_synergyFactor = factor;
}

void PayOffCalculator::setPunishmentBaseCost(const float cost)
{
    m_punishmentCostBase = cost;
}

void PayOffCalculator::setPunishmentBaseFine(const float fine)
{
    m_punishmentFineBase = fine;
}

void PayOffCalculator::setCooperationCost(const float cost)
{
    m_cooperationCost = cost;
}

void PayOffCalculator::allowPayoffBelowZero(const bool status)
{
    m_allowPayoffBelowZero = status;
}

void PayOffCalculator::setCounters(const std::array<unsigned int, 4>& counter)
{
    m_counter = counter;
}

void PayOffCalculator::calculateCosts(const int groupSize)
{
    //Precalculate costs, fines and payoffs

    int nPunishers = m_counter[FACTION_DEFECTOR] + m_counter[FACTION_MORALIST];
    m_punishmentCost = m_punishmentCostBase * nPunishers;
    
    int nMoralists = m_counter[FACTION_MORALIST] + m_counter[FACTION_IMMORALIST];
    m_punishmentFine = m_punishmentFineBase * nMoralists;

    int nCooperators = m_counter[FACTION_COOPERATOR] + m_counter[FACTION_MORALIST];
    m_payoff = m_synergyFactor * nCooperators / groupSize;
}

void PayOffCalculator::applyPayoff(rOrganism & organism)
{
    auto& pOrganism = organism.get();
        
    pOrganism.m_payoff += m_payoff;

    if (pOrganism.m_moralist) { //Subtract punishment costs from moralists/immoralists
        pOrganism.m_payoff -= m_punishmentCost;
    };

    if (!pOrganism.m_cooperated) {//Substract punishment fine from defectors/immoralists
        pOrganism.m_payoff -= m_punishmentFine;
    } else {
        pOrganism.m_payoff -= m_cooperationCost; //Substract 1 from cooperators / moralists
    }

    if (!m_allowPayoffBelowZero && pOrganism.m_payoff < 0) {
        pOrganism.m_payoff = 0;
    }
}

void PayOffCalculator::applyPayoff(Group & group)
{
    for (rOrganism& organism : group.data()) {
        applyPayoff(organism);
    }
}
