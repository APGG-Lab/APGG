#pragma once
#include <array>
#include "../Group.h"
#include "../Organism.h"

#include "PayoffCalculator.h"

namespace APGG {

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
