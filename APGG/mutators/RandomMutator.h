#pragma once
#include "Mutator.h"
namespace APGG {
    /**
    * Basic implementation of the Mutator base class that modifies Genomes of Organisms randomly.
    */
    class RandomMutator : public Mutator
    {
    public:
        void mutate(Grid& grid, const std::unordered_set<GridIndex>& selection);
		void configure(Config& config);
    };
}


