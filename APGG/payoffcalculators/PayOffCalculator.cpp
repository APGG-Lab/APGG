#include "PayOffCalculator.h"

namespace APGG {


    PayOffCalculator::PayOffCalculator() : m_synergyFactor(1), m_punishmentCostBase(1.0f), m_punishmentFineBase(1.0f), m_allowPayoffBelowZero(false)
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

        int nPunished = m_counter[Faction::Defector] + m_counter[Faction::Moralist];
        m_punishmentCost = m_punishmentCostBase * nPunished;

        int nMoralists = m_counter[Faction::Moralist] + m_counter[Faction::Immoralist];
        m_punishmentFine = m_punishmentFineBase * nMoralists;

        int nCooperators = m_counter[Faction::Cooperator] + m_counter[Faction::Moralist];
        m_payoff = m_synergyFactor * nCooperators / groupSize;
    }
}