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
	//	std::unordered_set<Organism*> m_organismPtr;
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
        void removeAndCleanupChildLists3(Organism& organism);
        void validate(const pOrganism& organism);
		void logIterative2(Organism* organism);

        void logTop();
		void wipe(Organism& organism) {


            Organism* parent = nullptr;
            Organism* organismPtr = &organism;

            if (!organismPtr->m_children2.empty()) {
                return;
            }

            if (organismPtr->m_parent2 != nullptr) {
                int test = 0;
                organismPtr->m_parent2->removeChild2(organismPtr);
                parent = organismPtr->m_parent2;
                organismPtr->m_parent2 = nullptr;
                organismPtr = parent;
                parent = nullptr;
            }

            // Use loop instead of a recursive function, because a recursive
            // function can crash the software, when the tree is too high
            while (organismPtr->m_children2.empty()) {  //Loop through until we find a organism with a child

                parent = organismPtr->m_parent2;

                organismPtr->m_parent2 = nullptr;

                if (organismPtr->m_status == Status::Copy) {
                 //   m_organismPtr.erase(organismPtr);
                    delete organismPtr;
                }

                if (parent != nullptr) {
                    parent->removeChild2(organismPtr);
                    organismPtr = parent;
                }
                else {
                    break;
                }
            }
		}
	};
}


