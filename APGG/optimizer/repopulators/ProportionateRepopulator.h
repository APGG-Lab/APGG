#pragma once
#include <iostream>
#include "Repopulator.h"

namespace APGG {

    class ProportionateRepupoluator : public Repopulator
    {
    public:
        void repopulate(std::shared_ptr<Grid>& grid, std::vector<rOrganism>& selection);
    };

}