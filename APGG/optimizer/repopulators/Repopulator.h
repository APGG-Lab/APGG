#pragma once
#include <vector>
#include "../../Grid.h"

class Repopulator
{
public:
    virtual void repopulate(std::shared_ptr<Grid>& grid, std::vector<rOrganism>& selection) = 0;
};