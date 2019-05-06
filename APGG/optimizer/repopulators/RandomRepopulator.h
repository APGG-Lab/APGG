#pragma once
#include "Repopulator.h"
class RandomRepopulator :
    public Repopulator
{
public:
    void repopulate(std::shared_ptr<Grid>& grid, std::vector<rOrganism>& selection);
};

