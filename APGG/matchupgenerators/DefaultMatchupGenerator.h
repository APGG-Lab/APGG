#pragma once
#include <vector>
#include <numeric>
#include "MatchupGenerator.h"
//typedef std::vector<pOrganism> Group;

namespace APGG {

    class DefaultMatchupGenerator : public MatchupGenerator
    {
    protected:
        std::vector<unsigned int> gridKeys;
        int numberOfGroups;
    public:
        void generateGroups(Grid& grid);
        void configure(Config& config);
    };

}