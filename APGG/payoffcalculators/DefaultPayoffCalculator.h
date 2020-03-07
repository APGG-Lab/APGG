#pragma once
#include <array>
#include "../Group.h"
#include "../Organism.h"

#include "PayOffCalculator.h"

namespace APGG {

    class DefaultPayOffCalculator : public PayOffCalculator
    {
    public:
        DefaultPayOffCalculator();
        void calculateCosts(Group& group);
        void applyPayoff(Organism& organism);
        void applyPayoff(Grid& grid, Group& group);
		void configure(Config& config);
    };

}