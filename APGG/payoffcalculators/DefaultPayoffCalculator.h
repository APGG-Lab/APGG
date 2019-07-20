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
        void calculateCosts(const int groupSize);
        void applyPayoff(rOrganism& organism);
        void applyPayoff(Group& group);
		void configure(Config& config);
    };

}