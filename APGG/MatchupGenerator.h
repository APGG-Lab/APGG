#pragma once
#include <vector>
#include <memory>

#include "Grid.h"
#include "Organism.h"
#include "Group.h"
//typedef std::vector<pOrganism> Group;

class MatchupGenerator
{
private:
    std::shared_ptr<Grid> m_grid;
    unsigned int m_groupSize;
    std::vector<Group> m_groups;
public:
    void setGrid(std::shared_ptr<Grid> grid);
    void setGroupSize(const unsigned int size);
    std::vector<Group> getGroups() const;
    void generateGroups();
};

