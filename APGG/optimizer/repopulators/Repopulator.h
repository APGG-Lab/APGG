#pragma once
#include <vector>
#include "../../grids/Grid.h"
#include <unordered_set>

namespace APGG {

    enum class RepopulatorType : uint8_t {Random = 0, Proportionate, Count};

    class Repopulator : public Configurable
    {
    public:
        virtual void repopulate(Grid& grid, std::unordered_set<unsigned int>& selection) = 0;
		virtual void configure(Config& config) = 0;
    };

}