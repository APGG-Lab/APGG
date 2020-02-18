#pragma once
#include "Mutator.h"
namespace APGG {
    class RandomMutator : public Mutator
    {
    public:
        void mutate(Grid& grid, const std::unordered_set<GridIndex>& selection);
		void configure(Config& config);
    };
}


