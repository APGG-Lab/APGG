#pragma once
#include <iostream>
#include "Repopulator.h"

namespace APGG {

    class ProportionateRepupoluator : public Repopulator
    {
    public:
        void repopulate(Grid& grid, std::unordered_set<GridIndex>& selection) override;
		void configure(Config& config) override;
    };

}