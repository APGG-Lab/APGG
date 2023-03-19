#pragma once
#include "Selector.h"

namespace APGG {

    /**
    * Basic implementation of the Selector base class that selects Organisms from a Grid based on their order after
    * sorting the Grid by fitness. 
    */
    class EliteSelector : public Selector
    {
    public:
        std::unordered_set<GridIndex>& select(Grid& grid);
		void configure(Config& config) override;
    };

}