#pragma once
#include <array>
#include <string>
#include "../Group.h"
#include "../Organism.h"
#include "../Configurable.h"
#include "../grids/Grid.h"
namespace APGG {

    constexpr unsigned int nPayoffTypes = 1;
    enum PayoffTypes { f };

    class PayoffCalculator : public Configurable
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
    public:
        PayoffCalculator();

        void setSynergyFactor(const float factor);
        void setPunishmentBaseCost(const float cost);
        void setPunishmentBaseFine(const float factor);
        void setCooperationCost(const float cost);
        void allowPayoffBelowZero(const bool status);

        virtual void calculateCosts(Group& group) = 0;
        virtual void applyPayoff(Grid& grid, Group& group) = 0;

        static std::unique_ptr<PayoffCalculator> Create(Config& config);
        virtual float calculateIndividualPayoff(Organism& organism) = 0;
    };

}
