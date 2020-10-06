#pragma once
#include <array>
#include "../Group.h"
#include "../Organism.h"

#include "PayoffCalculator.h"

namespace APGG {

    class GroupLevelPayoffCalculator : public PayoffCalculator
    {
    private:
        float m_individualism = 0.5f;
        float m_groupPayoffPool = 0.0f;
    public:
        GroupLevelPayoffCalculator();
        void calculateCosts(Group& group);
        void applyPayoff(Organism& organism);
        void applyPayoff(Grid& grid, Group& group);
        float calculateIndividualPayoff(Organism& organism);
		void configure(Config& config);
    };

}