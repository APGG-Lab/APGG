#pragma once
#include <vector>
#include <memory>

#include "../grids/DefaultGrid.h"
#include "../Organism.h"
#include "../Group.h"
//typedef std::vector<pOrganism> Group;

namespace APGG {

    class MatchupGenerator
    {
    protected:
        std::shared_ptr<Grid> m_grid;
        unsigned int m_groupSize;
        std::vector<Group> m_groups;
    public:
        void setGrid(std::shared_ptr<Grid> grid);
        void setGroupSize(const unsigned int size);
        std::vector<Group> getGroups() const;
        virtual void generateGroups() = 0;
    };

}