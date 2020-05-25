#pragma once
#include <array>
#include "../Group.h"
#include "../Organism.h"

#include "PayOffCalculator.h"

namespace APGG {

    class AsymmetricPayOffCalculator : public PayOffCalculator
    {
    public:
        AsymmetricPayOffCalculator();
        void calculateCosts(Group& group);
        void applyPayoff(Grid& grid, Group& group);
		void configure(Config& config);
        float calculateIndividualPayoff(Organism& organism);

        uint8_t getGenomeNumber() const override;
    };

}