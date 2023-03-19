#pragma once
#include <array>
#include "../Group.h"
#include "../Organism.h"

#include "PayoffCalculator.h"

namespace APGG {

    /**
    * Basic implementation of the PayoffCalculator base class that calculates individual payoff for every Organism
    * in a Group based on the different factions within this group and adds a payoff from the group as well. Does not
    * allow payoffs below zero.
    */
    class AsymmetricPayoffCalculator : public PayoffCalculator
    {
    private:
        float m_denominator;
        const std::array<unsigned int, 5> m_groupRanks = {
            5,
          4,1,3,
            2
        };

    public:
        AsymmetricPayoffCalculator();
        void calculateCosts(Group& group);
        void applyPayoff(Organism& organism);
        void applyPayoff(Grid& grid, Group& group);
        float calculateIndividualPayoff(Organism& organism);
		void configure(Config& config);
    };

}
