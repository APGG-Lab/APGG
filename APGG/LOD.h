#pragma once
#include <vector>
#include <list>
#include <unordered_set>
#include "Configurable.h"

#include "Organism.h"
#include "grids/Grid.h"
#include "archivers/Archiver.h"
#include "archivers/LODArchiver.h"
namespace APGG {
	class LOD
	{
	private:
        std::list<Organism*> m_pool;
	public:
		void createLOD(Grid& grid, const std::unordered_set<GridIndex>& selection);
		void createLODCopy(Grid& grid, Organism& organism);
        void removeAndCleanupChildLists(Organism& organism);

        void logTop(Grid& grid, LODArchiver& archiver);
        void cleanup(Grid& grid);
		void wipe(Organism& organism) 
        {


            Organism* parent = nullptr;
            Organism* organismPtr = &organism;

            if (!organismPtr->m_children.empty()) 
            {
                return;
            }

            if (organismPtr->m_parent != nullptr) 
            {
                organismPtr->m_parent->removeChild(organismPtr);
                parent = organismPtr->m_parent;
                organismPtr->m_parent = nullptr;
                organismPtr = parent;
                parent = nullptr;
            }

            // Use loop instead of a recursive function, because a recursive
            // function can crash the software, when the tree is too high
            while (organismPtr->m_children.empty()) 
            {  //Loop through until we find a organism with a child

                parent = organismPtr->m_parent;

                organismPtr->m_parent = nullptr;

                if (organismPtr->m_status == Status::Copy) 
                {
                    delete organismPtr;
                }

                if (parent != nullptr) 
                {
                    parent->removeChild(organismPtr);
                    organismPtr = parent;
                }
                else 
                {
                    break;
                }
            }
		}
	};
}


