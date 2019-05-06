#pragma once
#include <array>
#include "Group.h"
#include "Organism.h"

class PayOffCalculator
{
private:
    float m_synergyFactor;
    float m_punishmentCostBase;
    float m_punishmentFineBase;
    float m_cooperationCost;

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
    //@todo finde better name
    void setCounters(const std::array<unsigned int, 4>& counter);
    void calculateCosts(const int groupSize);
    void applyPayoff(rOrganism& organism);
    void applyPayoff(Group& group);
};

