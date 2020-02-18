#pragma once
#include <vector>
#include <numeric>
#include "MatchupGenerator.h"
//typedef std::vector<pOrganism> Group;

namespace APGG {

    class DefaultMatchupGenerator : public MatchupGenerator
    {
    protected:
        std::vector<GridIndex> gridKeys;
        int numberOfGroups;
    public:
        void generateGroups(Grid& grid);
        void configure(Config& config);
    };

}