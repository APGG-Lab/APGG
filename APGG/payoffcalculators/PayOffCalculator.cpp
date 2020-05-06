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
}