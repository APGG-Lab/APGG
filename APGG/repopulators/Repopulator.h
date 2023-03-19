#pragma once
#include <vector>
#include "../grids/Grid.h"
#include <unordered_set>

namespace APGG 
{
    /**
    * Base class for the repopulators. 
    */
    class Repopulator : public Configurable
    {
    public:
        virtual void repopulate(Grid& grid, std::unordered_set<GridIndex>& selection) = 0;
		virtual void configure(Config& config) = 0;

        static std::unique_ptr<Repopulator> Create(Config& config);
    };
}