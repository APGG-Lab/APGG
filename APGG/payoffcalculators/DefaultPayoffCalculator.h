#pragma once
#include <array>
#include "../Group.h"
#include "../Organism.h"

#include "PayoffCalculator.h"

namespace APGG {

    /**
    * Basic implementation of the PayoffCalculator base class that calculates individual payoff for every Organism
    * in a Group based on the different factions within this group.
    */
    class DefaultPayoffCalculator : public PayoffCalculator
    {
    public:
        DefaultPayoffCalculator();
        void calculateCosts(Group& group);
        void applyPayoff(Grid& grid, Group& group);
		void configure(Config& config);
        float calculateIndividualPayoff(Organism& organism);
    };

}