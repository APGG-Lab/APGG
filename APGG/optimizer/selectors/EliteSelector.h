#pragma once
#include "Selector.h"

class EliteSelector : public Selector
{
public:
    EliteSelector();
    EliteSelector(const unsigned int eliminationCount);
    std::vector<pOrganism> select(std::shared_ptr<Grid>& grid);
};

