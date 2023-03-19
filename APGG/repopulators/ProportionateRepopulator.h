#pragma once
#include <iostream>
#include "Repopulator.h"

namespace APGG {

    /**
    * Basic implementation of the Repopulator base class that repopulates eliminated Organisms with parent candidates chosen randomly
    * and then decided upon by the payoff they might provide.
    */
    class ProportionateRepupoluator : public Repopulator
    {
    public:
        void repopulate(Grid& grid, std::unordered_set<GridIndex>& selection);
		void configure(Config& config);
    };

}