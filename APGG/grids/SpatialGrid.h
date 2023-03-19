#pragma once
#include <cassert>
#include <algorithm>
#include <numeric>

#include "../Organism.h"
#include "Grid.h"


namespace APGG {
	/**
	* Basic implementation of the Grid base class that generates Groups based upon spatial relation within
	* the Grid. 
	*/
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