#pragma once
#include "Repopulator.h"

namespace APGG {

    /**
    * Basic implementation of the Repopulator base class that repopulates eliminated Organisms with neighbors as parents.
    */
    class SpatialRepopulator :
        public Repopulator
    {
    public:
        void repopulate(Grid& grid, std::unordered_set<GridIndex>& selection);
        void configure(Config& config);

    protected:
        unsigned int m_width = 0;
        unsigned int m_height = 0;
        unsigned int m_totalSize = 0;

        // Helper function for the edges of the grid to wrap around to the other side if neighbors are requested.
        GridIndex wrap(int x, int y);
    };

}