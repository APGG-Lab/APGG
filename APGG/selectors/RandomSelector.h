#pragma once
#include "Selector.h"
#include <unordered_set>
namespace APGG {

    /**
    * Basic implementation of the Selector base class that selects random Organisms from a Grid.
    */
    class RandomSelector : public Selector
    {
    public:
        RandomSelector();
        RandomSelector(const unsigned int eliminationCount);
        std::unordered_set<GridIndex>& select(Grid& grid);
		void configure(Config& config);
    };
}