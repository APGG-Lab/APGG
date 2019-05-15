#include "LOD.h"

namespace APGG {


	LOD::LOD()
	{
	}


	LOD::~LOD()
	{
	}

	void LOD::setGrid(std::shared_ptr<Grid> grid) {
		m_grid = grid;
	}


	void LOD::LODebug(std::shared_ptr<Grid> grid, std::vector<rOrganism>& selection) {
		m_grid = grid;
		for (rOrganism& deadOrganism : selection)
		{
			pOrganism pDeadOrganism = deadOrganism.get().getPtr();

			if (!pDeadOrganism->m_children.empty()) {
				createLODCopy(pDeadOrganism);
			}

            Organism::removeAndCleanupChildLists(pDeadOrganism);

			pDeadOrganism->m_parent = nullptr;
			pDeadOrganism->m_children.clear();
		}

		
	}

	void LOD::createLODCopy(pOrganism & organism) {
		pOrganism organismLODCopy = std::make_shared<Organism>();
		organism->copyTo(organismLODCopy);
#ifdef DEBUG_EXTREME
        std::cout << "LOD: Original is " << "Ptr:" << organism.get()  << " ID: " << organism->ID   << " Parent: " << organism->getParentID() << " Children: " << organism->getChildIDs() << std::endl;
        std::cout << "LOD: Copy     is " << "Ptr:" << organismLODCopy.get() << " ID: " << organismLODCopy->ID   << " Parent: " << organismLODCopy->getParentID() << " Children: " << organismLODCopy->getChildIDs() << std::endl;
#endif
		organismLODCopy->m_generation = m_grid->getGeneration();

		if (organism->m_parent.get() != nullptr)
		{
#ifdef DEBUG_EXTREME
            std::cout << "LOD: Remove child from parent. Before ParentChildsize: " << organismLODCopy->m_parent->m_children.size();
#endif
			organismLODCopy->m_parent->m_children.remove(organism);
			organismLODCopy->m_parent->m_children.push_back(organismLODCopy);
#ifdef DEBUG_EXTREME
            std::cout << " After ParentChildSize:" << organismLODCopy->m_parent->m_children.size() << std::endl;
#endif

		}
		for (pOrganism& child : organism->m_children) {
#ifdef DEBUG_EXTREME
            std::cout << "LOD: Set new parent PTR for child: " << child->ID << " Before ParentPTR: " << child->m_parent.get() << " ID:" << child->getParentID();
#endif
			child->m_parent = organismLODCopy;
			child->ParentStatus = PARENT_MODIFIED;
#ifdef DEBUG_EXTREME
            std::cout << " After ParentPTR: " << child->m_parent.get() << " ID:" << child->getParentID() << std::endl;
#endif
		}

#ifdef DEBUG_EXTREME
        std::cout << "LOD: Remove references to parent and children: " << std::endl;
#endif

		organism->m_parent = nullptr;
		organism->m_children.clear();
		organism->ID = -1;
        organism->m_status = STATUS_ORIGINAL;
        organism->ParentStatus = PARENT_ORIGINAL;

#ifdef DEBUG_EXTREME
        std::cout << "LOD: Original is " << "Ptr:" << organism.get() << " ID: " << organism->ID << " Parent: " << organism->getParentID() << " Children: " << organism->getChildIDs() << std::endl;
#endif

		//organism->m_history += "(F," + std::to_string(m_grid->getGeneration()) + "," + std::to_string(organism->ID) + ")|";
		//organismLODCopy->m_history += "(L," + std::to_string(m_grid->getGeneration()) + "," + std::to_string(organismLODCopy->ID) + ")|";
	}

}