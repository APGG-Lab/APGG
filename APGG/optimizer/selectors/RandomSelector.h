#pragma once
#include "Selector.h"
#include <unordered_set>
namespace APGG {

    class RandomSelector : public Selector
    {
    public:
        RandomSelector();
        RandomSelector(const unsigned int eliminationCount);
        std::unordered_set<unsigned int>& select(Grid& grid);
		void configure(Config& config);
    };

}