#pragma once
#include "Repopulator.h"

namespace APGG {

    class RandomRepopulator :
        public Repopulator
    {
    public:
        void repopulate(Grid& grid, std::unordered_set<GridIndex>& selection);
        void configure(Config& config);
    };

}