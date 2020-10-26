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
		int numberOfGroups;

	public:
		
		void generateGroups() override;

		void configure(Config& config) override;
	};
}