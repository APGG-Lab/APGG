#pragma once
#include "Repopulator.h"
class ProportionateRepupoluator : public Repopulator
{
public:
	void repopulate(std::shared_ptr<Grid>& grid, std::vector<rOrganism>& selection);
};

