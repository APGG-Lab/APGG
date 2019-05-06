#pragma once
#include <vector>
#include "../../Grid.h"

namespace APGG {

    constexpr unsigned int nRepopulatorTypes = 2;
    enum RepopulatorTypes {REPOPULATOR_RANDOM, REPOPULATOR_PROPORTIONATE};

    class Repopulator
    {
    public:
        virtual void repopulate(std::shared_ptr<Grid>& grid, std::vector<rOrganism>& selection) = 0;
    };

}