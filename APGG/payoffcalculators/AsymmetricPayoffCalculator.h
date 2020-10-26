#pragma once
#include <array>
#include "../Group.h"
#include "../Organism.h"

#include "PayoffCalculator.h"

namespace APGG {

    class AsymmetricPayoffCalculator : public PayoffCalculator
    {
    private:
        float m_denominator = 0;
        const std::array<unsigned int, 5> m_groupRanks = {
            5,
          4,1,3,
            2
        };

    public:
        AsymmetricPayoffCalculator();
        void calculateCosts(Group& group) override;
        void applyPayoff(Organism& organism);
        void applyPayoff(Grid& grid, Group& group) override;
        float calculateIndividualPayoff(Organism& organism) override;
		void configure(Config& config) override;
    };

}
