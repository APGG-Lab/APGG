#pragma once
#include <cassert>
#include <algorithm>
#include <numeric>

#include "../Organism.h"
#include "Grid.h"


namespace APGG {
	class SpatialGrid : public Grid
	{
	protected:
		int numberOfGroups;
		bool m_built = false;
		GridIndex wrap(int x, int y);
	public:
		
		void generateGroups();

		void configure(Config& config) override;
	};
}