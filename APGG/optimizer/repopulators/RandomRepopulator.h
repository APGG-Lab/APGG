#pragma once
#include "Repopulator.h"

namespace APGG {

    class RandomRepopulator :
        public Repopulator
    {
    public:
        void repopulate(std::shared_ptr<Grid>& grid, std::vector<rOrganism>& selection);
		void configure(Config& config);
    };

}