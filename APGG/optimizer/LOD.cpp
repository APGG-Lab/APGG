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

		for (rOrganism& rDeadOrganism : selection)
		{            
			if (!rDeadOrganism.get().m_children.empty()) {
				createLODCopy(rDeadOrganism);
         //       validate(rDeadOrganism.get().getPtr());

            }
            else {
                pOrganism porganism = rDeadOrganism.get().getPtr();
                removeAndCleanupChildLists(porganism);
                porganism.reset();
          //      validate(rDeadOrganism.get().getPtr());

            }




			

            if (rDeadOrganism.get().m_parent != nullptr) {
                rDeadOrganism.get().m_parent->removeChild(rDeadOrganism.get().getPtr());
                rDeadOrganism.get().m_parent = nullptr;
            }


            //pDeadOrganism->m_parent.reset();
            //for (auto& child : pDeadOrganism->m_children) {
            //    child.reset();
            //}
		}

		
	}

	void LOD::createLODCopy(pOrganism & organism) {
//		pOrganism organismLODCopy = std::make_shared<Organism>();
//		organism->copyTo(organismLODCopy);
//#ifdef DEBUG_EXTREME
//        std::cout << "LOD: Original is " << "Ptr:" << organism.get()  << " ID: " << organism->ID   << " Parent: " << organism->getParentID() << " Children: " << organism->getChildIDs() << std::endl;
//        std::cout << "LOD: Copy     is " << "Ptr:" << organismLODCopy.get() << " ID: " << organismLODCopy->ID   << " Parent: " << organismLODCopy->getParentID() << " Children: " << organismLODCopy->getChildIDs() << std::endl;
//#endif
//		organismLODCopy->m_generation = m_grid->getGeneration();
//
//		if (organism->m_parent.get() != nullptr)
//		{
//#ifdef DEBUG_EXTREME
//            std::cout << "LOD: Remove child from parent. Before ParentChildsize: " << organismLODCopy->m_parent->m_children.size();
//#endif
//			organismLODCopy->m_parent->m_children.remove(organism);
//			organismLODCopy->m_parent->m_children.push_back(organismLODCopy);
//#ifdef DEBUG_EXTREME
//            std::cout << " After ParentChildSize:" << organismLODCopy->m_parent->m_children.size() << std::endl;
//#endif
//
//		}
//		for (pOrganism& child : organism->m_children) {
//#ifdef DEBUG_EXTREME
//            std::cout << "LOD: Set new parent PTR for child: " << child->ID << " Before ParentPTR: " << child->m_parent.get() << " ID:" << child->getParentID();
//#endif
//			child->m_parent = organismLODCopy;
//			child->ParentStatus = PARENT_MODIFIED;
//#ifdef DEBUG_EXTREME
//            std::cout << " After ParentPTR: " << child->m_parent.get() << " ID:" << child->getParentID() << std::endl;
//#endif
//		}
//
//#ifdef DEBUG_EXTREME
//        std::cout << "LOD: Remove references to parent and children: " << std::endl;
//#endif
//
//		organism->m_parent.reset();
//        for (auto& child : organism->m_children) {
//            child.reset();
//        }
//		//organism->m_children.clear();
//		organism->ID = -1;
//        organism->m_status = STATUS_ORIGINAL;
//        organism->ParentStatus = PARENT_ORIGINAL;
//
//#ifdef DEBUG_EXTREME
//        std::cout << "LOD: Original is " << "Ptr:" << organism.get() << " ID: " << organism->ID << " Parent: " << organism->getParentID() << " Children: " << organism->getChildIDs() << std::endl;
//#endif
//
//		//organism->m_history += "(F," + std::to_string(m_grid->getGeneration()) + "," + std::to_string(organism->ID) + ")|";
//		//organismLODCopy->m_history += "(L," + std::to_string(m_grid->getGeneration()) + "," + std::to_string(organismLODCopy->ID) + ")|";
	}

    void LOD::createLODCopy(rOrganism & rorganism) {
        if (rorganism.get().m_status >= 2) {
            int test = 0;
        }
        Organism& organism = rorganism.get();
        pOrganism organismLODCopy = std::make_shared<Organism>();

        organism.copyTo(organismLODCopy);

        DEBUG_MSG("LOD: Original is " + organism.getDebugString());
        DEBUG_MSG("LOD: Copy     is " + organismLODCopy->getDebugString());

        //@todo : think about removing this line. Copy should have same ID and Generation
        organismLODCopy->m_generation = m_grid->getGeneration();
        
        if (organism.m_parent != nullptr)
        {
            DEBUG_MSG("LOD: Remove old organism from parent and add the new one");

            organismLODCopy->m_parent->removeChild(organism.getPtr());
        	organismLODCopy->m_parent->addChild(organismLODCopy);
        }
        		for (pOrganism& child : organism.m_children) {
                    DEBUG_MSG("LOD: Set new paraent for child before: " + child->getDebugString());

        			child->m_parent = organismLODCopy;
        			child->ParentStatus = PARENT_MODIFIED;

                    DEBUG_MSG("LOD: Set new paraent for child after: " + child->getDebugString());
        		}
        
                DEBUG_MSG("LOD: Remove references to parent and children");
        
        		organism.m_parent.reset();
                for (auto& child : organism.m_children) {
                    child.reset();
                }
                organism.clearChilds();
        		//organism->m_children.clear();
        		organism.ID = -1;
                organism.m_status = STATUS_ORIGINAL;
                organism.ParentStatus = PARENT_ORIGINAL;
        
                DEBUG_MSG("LOD: Original after lodCopy: " + organism.getDebugString());

              //  m_externalList.push_back(organismLODCopy);        
        		//organism->m_history += "(F," + std::to_string(m_grid->getGeneration()) + "," + std::to_string(organism->ID) + ")|";
        		//organismLODCopy->m_history += "(L," + std::to_string(m_grid->getGeneration()) + "," + std::to_string(organismLODCopy->ID) + ")|";
    }


    void LOD::removeAndCleanupChildLists(pOrganism& organism) {
        if (!organism->m_children.empty()) {
            DEBUG_MSG("LOD Cleanup: organism has children " + organism->getDebugString());
            return;
        }
        
        if (organism->m_parent == nullptr) {
            DEBUG_MSG("LOD Cleanup: found root organism " + organism->getDebugString());
            return;
        }

        pOrganism parent = organism->m_parent;


        organism->m_parent->removeChild(organism);
        organism->m_status = STATUS_DELETED;
        organism->m_parent.reset();
       // m_externalList.remove(organism);
        parent->removeChild(organism);
        
        if (parent->m_status != STATUS_CLONE) {
            DEBUG_MSG("LOD Cleanup: organism is not a clone " + organism->getDebugString());
            return;
        }

        removeAndCleanupChildLists(parent);
        parent.reset();

        DEBUG_MSG("LOD Cleanup: done " + organism->getDebugString());
    }
}