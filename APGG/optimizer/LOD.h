#pragma once
#include <vector>
#include <list>

#include "../Organism.h"
#include "../grids/Grid.h"
#include "../archivers/Archiver.h"
#include "../archivers/LODArchiver.h"

namespace APGG {
	class LOD
	{
	private:
		std::shared_ptr<Grid> m_grid;
        void logRecursive(const pOrganism& organism);
        std::unique_ptr<LODArchiver> m_archiver;
	public:
        void setArchiver(std::unique_ptr<LODArchiver>& archiver);
		void setGrid(const std::shared_ptr<Grid>& grid);
		void LODebug(std::vector<rOrganism>& organism);
		void createLODCopy(rOrganism& organism);
        void removeAndCleanupChildLists(pOrganism& organism);
        void validate(const pOrganism& organism);
        void logTop();
	};
}


