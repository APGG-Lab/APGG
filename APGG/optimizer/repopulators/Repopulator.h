#pragma once
#include <vector>
#include "../../grids/Grid.h"

namespace APGG {

    enum class RepopulatorType : uint8_t {Random = 0, Proportionate, Count};

    class Repopulator : public Configurable
    {
    public:
        virtual void repopulate(std::shared_ptr<Grid>& grid, std::vector<rOrganism>& selection) = 0;
		virtual void configure(Config& config) = 0;
    };

}