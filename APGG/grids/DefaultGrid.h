#pragma once
#include <cassert>
#include <algorithm>
#include <numeric>

#include "../Organism.h"
#include "Grid.h"


namespace APGG {
	/**
	* Basic implementation of the Grid base class that generates Groups out of randomly chosen Organisms.
	*/
	class DefaultGrid : public Grid
	{
	protected:
		int numberOfGroups;

	public:
		
		void generateGroups();

		void configure(Config& config) override;
	};
}