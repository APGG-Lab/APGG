#pragma once
#include <array>
#include "../Group.h"
#include "../Organism.h"

#include "PayoffCalculator.h"

namespace APGG {

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