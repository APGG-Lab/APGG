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
        #ifdef DEBUG_EXTREME
                std::cout << "LOD: Original is " << "Ptr:" << organism.get()  << " ID: " << organism->ID   << " Parent: " << organism->getParentID() << " Children: " << organism->getChildIDs() << std::endl;
                std::cout << "LOD: Copy     is " << "Ptr:" << organismLODCopy.get() << " ID: " << organismLODCopy->ID   << " Parent: " << organismLODCopy->getParentID() << " Children: " << organismLODCopy->getChildIDs() << std::endl;
        #endif
        		organismLODCopy->m_generation = m_grid->getGeneration();
        
        		if (organism.m_parent != nullptr)
        		{
        #ifdef DEBUG_EXTREME
                    std::cout << "LOD: Remove child from parent. Before ParentChildsize: " << organismLODCopy->m_parent->m_children.size();
        #endif
                    organismLODCopy->m_parent->removeChild(organism.getPtr());
        			organismLODCopy->m_parent->addChild(organismLODCopy);
        #ifdef DEBUG_EXTREME
                    std::cout << " After ParentChildSize:" << organismLODCopy->m_parent->m_children.size() << std::endl;
        #endif
        
        		}
        		for (pOrganism& child : organism.m_children) {
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
        
        		organism.m_parent.reset();
                for (auto& child : organism.m_children) {
                    child.reset();
                }
                organism.clearChilds();
        		//organism->m_children.clear();
        		organism.ID = -1;
                organism.m_status = STATUS_ORIGINAL;
                organism.ParentStatus = PARENT_ORIGINAL;
        
        #ifdef DEBUG_EXTREME
                std::cout << "LOD: Original is " << "Ptr:" << organism.get() << " ID: " << organism->ID << " Parent: " << organism->getParentID() << " Children: " << organism->getChildIDs() << std::endl;
        #endif

              //  m_externalList.push_back(organismLODCopy);        
        		//organism->m_history += "(F," + std::to_string(m_grid->getGeneration()) + "," + std::to_string(organism->ID) + ")|";
        		//organismLODCopy->m_history += "(L," + std::to_string(m_grid->getGeneration()) + "," + std::to_string(organismLODCopy->ID) + ")|";
    }


    void LOD::removeAndCleanupChildLists(pOrganism& organism) {
        if (!organism->m_children.empty()) {
#ifdef DEBUG_EXTREME
            std::cout << "Cleanup organism is not dead: " << "Ptr:" << organism.get() << " ID: " << organism->ID << " Parent: " << organism->getParentID() << " Children: " << organism->getChildIDs() << std::endl;
#endif
            return;
        }
        
        if (organism->m_parent == nullptr) {
#ifdef DEBUG_EXTREME
            std::cout << "Cleanup organism origin reached: " << "Ptr:" << organism.get() << " ID: " << organism->ID << " Parent: " << organism->getParentID() << " Children: " << organism->getChildIDs() << " Gen:" << organism->m_generation << std::endl;
#endif
            return;
        }

        pOrganism parent = organism->m_parent;


        organism->m_parent->removeChild(organism);
        organism->m_status = STATUS_DELETED;
        organism->m_parent.reset();
       // m_externalList.remove(organism);
        parent->removeChild(organism);
        
        if (parent->m_status != STATUS_CLONE) {
#ifdef DEBUG_EXTREME
            std::cout << "Cleanup organism is not a clone: " << "Ptr:" << organism.get() << " ID: " << organism->ID << " Parent: " << organism->getParentID() << " Children: " << organism->getChildIDs() << std::endl;
#endif // DEBUG_EXTREME
            return;
        }

        removeAndCleanupChildLists(parent);
        parent.reset();

#ifdef DEBUG_EXTREME
        std::cout << "Cleanup organism done: " << "Ptr:" << organism.get() << " ID: " << organism->ID << " Parent: " << organism->getParentID() << " Children: " << organism->getChildIDs() << " Gen:" << organism->m_generation << std::endl;
#endif // DEBUG_EXTREME

    }
}