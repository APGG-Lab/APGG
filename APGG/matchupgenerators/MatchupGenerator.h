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
        std::vector<Group> m_groups;
    public:
        void configure(Config& config);
        virtual void setGroupSize(const unsigned int size);
        virtual std::vector<Group>& getGroups();

        virtual void generateGroups(Grid& grid) = 0;
    };

}