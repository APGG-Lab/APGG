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
        float m_synergyFactor = 1.0f;
        float m_punishmentCostBase = 1.0f;
        float m_punishmentFineBase = 1.0f;
        float m_cooperationCost = 1.0f;
        bool m_allowPayoffBelowZero = false;

        float m_punishmentCost = 0.0f;
        float m_punishmentFine = 0.0f;
        float m_payoff = 0.0f;
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
