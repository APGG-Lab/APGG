#pragma once
#include <vector>
#include <numeric>
#include "MatchupGenerator.h"
//typedef std::vector<pOrganism> Group;

namespace APGG {

    class DefaultMatchupGenerator : public MatchupGenerator
    {
    public:
        void generateGroups();
    };

}