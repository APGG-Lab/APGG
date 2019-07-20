#pragma once
#include <array>
#include <string>
#include "../Group.h"
#include "../Organism.h"
#include "../Configurable.h"

namespace APGG {

    constexpr unsigned int nPayOffTypes = 1;
    enum PayOffTypes { PAYOFF_DEFAULT };

    class PayOffCalculator : public Configurable
    {
    protected:
        float m_synergyFactor;
        float m_punishmentCostBase;
        float m_punishmentFineBase;
        float m_cooperationCost;
        bool m_allowPayoffBelowZero;

        float m_punishmentCost;
        float m_punishmentFine;
        float m_payoff;
        std::array<unsigned int, 4> m_counter;
    public:
        PayOffCalculator();

        void setSynergyFactor(const float factor);
        void setPunishmentBaseCost(const float cost);
        void setPunishmentBaseFine(const float factor);
        void setCooperationCost(const float cost);
        void allowPayoffBelowZero(const bool status);
        //@todo find better name
        void setCounters(const std::array<unsigned int, 4>& counter);
        virtual void calculateCosts(const int groupSize) = 0;
        virtual void applyPayoff(rOrganism& organism) = 0;
        virtual void applyPayoff(Group& group) = 0;
    };

}