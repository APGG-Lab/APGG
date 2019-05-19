#pragma once
#include <vector>
#include <list>

#include "../Organism.h"
#include "../Grid.h"

namespace APGG {
	class LOD
	{
	private:
		std::shared_ptr<Grid> m_grid;
        void printRecursive(const pOrganism& organism);
	public:
		void setGrid(const std::shared_ptr<Grid>& grid);
		void LODebug(std::vector<rOrganism>& organism);
		void createLODCopy(rOrganism& organism);
        void removeAndCleanupChildLists(pOrganism& organism);
        void validate(const pOrganism& organism);
        void printTop();
	};
}


