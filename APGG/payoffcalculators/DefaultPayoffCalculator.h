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
        void calculateCosts(Group& group) override;
        void applyPayoff(Grid& grid, Group& group) override;
		void configure(Config& config) override;
        float calculateIndividualPayoff(Organism& organism) override;
    };

}