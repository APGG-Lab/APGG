#pragma once
#include "Repopulator.h"

namespace APGG {

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

        GridIndex wrap(int x, int y);
    };

}