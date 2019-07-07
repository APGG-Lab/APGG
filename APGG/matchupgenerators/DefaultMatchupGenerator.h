#pragma once
#include <vector>
#include <memory>

#include "../grids/DefaultGrid.h"
#include "../Organism.h"
#include "../Group.h"
#include "MatchupGenerator.h"
//typedef std::vector<pOrganism> Group;

namespace APGG {

    class DefaultMatchupGenerator : public MatchupGenerator
    {

    public:
        void generateGroups();
    };

}