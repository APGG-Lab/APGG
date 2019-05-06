#pragma once
#include "Selector.h"

class RandomSelector : public Selector
{
public:
	RandomSelector();
	RandomSelector(const unsigned int eliminationCount);
    std::vector<pOrganism> select(std::shared_ptr<Grid>& grid);
};

