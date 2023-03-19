#pragma once
#include "Repopulator.h"

namespace APGG {

    /**
    * Basic implementation of the Repopulator base class that repopulates eliminated Organisms with random parents.
    */
    class RandomRepopulator :
        public Repopulator
    {
    public:
        void repopulate(Grid& grid, std::unordered_set<GridIndex>& selection);
        void configure(Config& config);
    };

}