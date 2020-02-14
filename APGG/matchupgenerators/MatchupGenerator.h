#pragma once
#include <vector>
#include <memory>

#include "../grids/DefaultGrid.h"
#include "../Organism.h"
#include "../Group.h"
#include "../Configurable.h"
//typedef std::vector<pOrganism> Group;

namespace APGG {

    class MatchupGenerator : public Configurable
    {
    protected:
        unsigned int m_groupSize;
        Grid* m_grid;
        std::vector<Group> m_groups;
    public:
        void configure(Config& config);
        virtual void setGrid(Grid* grid);
        virtual void setGroupSize(const unsigned int size);
        virtual std::vector<Group>& getGroups();

        virtual void generateGroups() = 0;
    };

}