#pragma once
#include <iostream>
#include "Repopulator.h"

namespace APGG {

    class ProportionateRepupoluator : public Repopulator
    {
    public:
        void repopulate(Grid& grid, std::unordered_set<unsigned int>& selection);
		void configure(Config& config);
    };

}