#pragma once
#include "Selector.h"
#include <unordered_set>
namespace APGG {

    class RandomSelector : public Selector
    {
    public:
        RandomSelector();
        explicit RandomSelector(const unsigned int eliminationCount);
        std::unordered_set<GridIndex>& select(Grid& grid) override;
		void configure(Config& config) override;
    };

}