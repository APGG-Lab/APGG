#pragma once
#include "../Organism.h"
#include "../Grid.h"
#include <vector>

namespace APGG {
	class LOD
	{
	private:
		std::shared_ptr<Grid> m_grid;
	public:
		LOD();
		void setGrid(std::shared_ptr<Grid> grid);
		void LODebug(std::shared_ptr<Grid> grid, std::vector<rOrganism>& organism);
		void createLODCopy(pOrganism& organism);
		~LOD();
	};
}


