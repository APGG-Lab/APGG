#pragma once
#include <vector>
#include <list>
#include <unordered_set>

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
        void logIterative(pOrganism& organism);
       // std::unique_ptr<LODArchiver> m_archiver;
	public:
        void setArchiver(std::unique_ptr<LODArchiver>& archiver);
		void setGrid(const std::shared_ptr<Grid>& grid);
		void LODebug(std::vector<rOrganism>& organism);
		void LOD2(Grid& grid, const std::unordered_set<unsigned int>& selection);
		void createLODCopy(rOrganism& organism);
		void createLODCopy2(Grid& grid, Organism& organism);
        void removeAndCleanupChildLists(pOrganism& organism);
        void removeAndCleanupChildLists2(Organism& organism);
        void validate(const pOrganism& organism);
		void logIterative2(Organism* organism);

        void logTop();
	};
}


