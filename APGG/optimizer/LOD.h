#pragma once
#include "../Organism.h"
#include "../Grid.h"
#include <vector>
#include <list>

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
		void createLODCopy(rOrganism& organism);
        void removeAndCleanupChildLists(pOrganism& organism);
        std::list<pOrganism> m_externalList;
        void wipe() {
            std::list<pOrganism> myList;

            for (auto& organism : m_externalList) {
                recursiveDelete(organism, myList);
            }
            for (auto& organism : myList) {
                for (auto& child : organism->m_children) {
                    child.reset();
                }
                organism->clearChilds();
                organism->m_parent.reset();
                organism->m_parent = nullptr;
            }
            myList.clear();
            m_externalList.clear();
        }
        void recursiveDelete(pOrganism& organism, std::list<pOrganism>& list) {
            organism->clearChilds();
            list.push_back(organism);
            if (organism->m_parent != nullptr) {
                recursiveDelete(organism->m_parent, list);
            }
        }

        void validate(const pOrganism& organism) {
            if (organism->m_children.size() > 0) {
                int test = 0;
            }
            if (organism->m_parent != nullptr) {
                int test = 0;
            }
        }
		~LOD();
	};
}


