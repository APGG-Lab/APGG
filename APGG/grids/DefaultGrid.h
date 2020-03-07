#pragma once
#include <cassert>
#include <algorithm>
#include <numeric>

#include "../Organism.h"
#include "Grid.h"


namespace APGG {
	class DefaultGrid : public Grid
	{
	protected:
		std::vector<GridIndex> gridKeys;
		int numberOfGroups;

	public:
		
		void generateGroups();

		void configure(Config& config) override;
	};
}