#include "LOD.h"

namespace APGG {

	void LOD::setGrid(const std::shared_ptr<Grid>& grid) {
	//	m_grid = grid;
	}


	void LOD::LODebug(std::vector<rOrganism>& selection) {
//		for (rOrganism& rDeadOrganism : selection)
//		{            
//			if (!rDeadOrganism.get().m_children.empty()) {
//				createLODCopy(rDeadOrganism);
//            }
//            else {
//                pOrganism porganism = rDeadOrganism.get().getPtr();
//                removeAndCleanupChildLists(porganism);
//                porganism.reset();
//            }
//
//#ifdef DEBUG_EXTREME
//            validate(rDeadOrganism.get().getPtr());
//#endif // DEBUG_EXTREME
//
//            if (rDeadOrganism.get().m_parent != nullptr) {
//                rDeadOrganism.get().m_parent->removeChild(rDeadOrganism.get().getPtr());
//                rDeadOrganism.get().m_parent = nullptr;
//            }
//
//		}

		
	}

    void LOD::LOD2(Grid& grid, const std::unordered_set<unsigned int>& selection)
    {
        for (const unsigned int& index : selection) {

            Organism& organism = grid[index];

            if (!organism.m_children.empty()) {
                // Organism has children. Create a copy of the organism
                // and change the Pointers of the parent and the children 
                // to point to the new copy of the organism

                createLODCopy2(grid, organism);
            }
            else {
                // Organsim doesn't have children. The tree reached a dead end.
                // Go upwards and remove all dead parents recursively

                removeAndCleanupChildLists2(organism);
            }
        }
    }

    void LOD::createLODCopy(rOrganism & rorganism) {
        //Organism& organism = rorganism.get();
        //pOrganism organismLODCopy = std::make_shared<Organism>();

        //organism.copyTo(organismLODCopy);

        //DEBUG_MSG("LOD: Original is " + organism.getDebugString());
        //DEBUG_MSG("LOD: Copy     is " + organismLODCopy->getDebugString());

        ////@todo : think about removing this line. Copy should have same ID and Generation
        //organismLODCopy->m_generation = m_grid->getGeneration();
        //
        //if (organism.m_parent != nullptr)
        //{
        //    DEBUG_MSG("LOD: Remove old organism from parent and add the new one");

        //    organismLODCopy->m_parent->removeChild(organism.getPtr());
        //	organismLODCopy->m_parent->addChild(organismLODCopy);
        //}
        //		for (pOrganism& child : organism.m_children) {
        //            DEBUG_MSG("LOD: Set new paraent for child before: " + child->getDebugString());
        //			child->m_parent = organismLODCopy;
        //            DEBUG_MSG("LOD: Set new paraent for child after: " + child->getDebugString());
        //		}
        //
        //        DEBUG_MSG("LOD: Remove references to parent and children");
        //
        //		organism.m_parent.reset();
        //        organism.clearChildren();
        //		organism.ID = -1;
        //        organism.m_status = STATUS_ORIGINAL;
        //
        //        DEBUG_MSG("LOD: Original after lodCopy: " + organism.getDebugString());
    }

    void LOD::createLODCopy2(Grid& grid, Organism& organism)
    {
        Organism* organismCopy = new Organism();

        organism.copyTo(organismCopy); //Copy all values to the new organism

        // Only root nodes shoudln't have a parent. IF should be true
        // in 99% of the time
        if (organism.m_parent != nullptr) { 
            // Replace the original organism with the new copy.
            // Therefore we've to replace the organism in the parent
            // organsim as well
            organismCopy->m_parent->removeChild(&organism);
            organismCopy->m_parent->addChild(organismCopy);
        }

        for (Organism* child : organism.m_children) {
            // We also have to change the parent of the children 
            // with the new copy
            child->m_parent = organismCopy;
        }

        //Cleanup the organism
        organism.m_parent = nullptr;
        organism.clearChildren();
#ifdef __DEBUG1
        organism.ID = -1;
#endif
    }


    void LOD::removeAndCleanupChildLists(pOrganism& organism) {
       /* if (!organism->m_children.empty()) {
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


        parent->removeChild(organism);
        
        if (parent->m_status != STATUS_CLONE) {
            DEBUG_MSG("LOD Cleanup: organism is not a clone " + organism->getDebugString());
            return;
        }

        removeAndCleanupChildLists(parent);
        parent.reset();

        DEBUG_MSG("LOD Cleanup: done " + organism->getDebugString());*/
    }

    void LOD::removeAndCleanupChildLists2(Organism& organism)
    {

            Organism* parent = nullptr;
            Organism* organismPtr = &organism;

            if (organismPtr->m_parent == nullptr) {
                //First iteration is always alive
                //Organism doesn't have a parent => nothing to do
                return;
            }

            parent = organismPtr->m_parent;
            parent->removeChild(organismPtr);
            organismPtr->m_parent = nullptr;


            organismPtr = parent;


            // Use loop instead of a recursive function, because a recursive
            // function can crash the software, when the tree is too high
            while (organismPtr->m_children.empty()) {  //Loop through until we find a organism with a child

                if (organismPtr->m_status == Status::Original) {
                    return;
                }

                parent = organismPtr->m_parent;

           //     m_organismPtr.erase(organismPtr);
                delete organismPtr;

                if (parent != nullptr) {
                    parent->removeChild(organismPtr);
                    organismPtr = parent;
                }
                else {
                    break;
                }
            }
    }


    void LOD::validate(const pOrganism& organism) {
        ////Something is terribly wrong if you see these messages in your console
        //if (organism->m_children.size() > 0) {
        //    DEBUG_MSG("LOD Validator: Dead Organism has children " + organism->getDebugString());
        //}
        //if (organism->m_parent != nullptr) {
        //    DEBUG_MSG("LOD Validator: Dead Organism has a parent " + organism->getDebugString());
        //}
    }

    void LOD::logRecursive(const pOrganism& organism) {
       /* if (organism->m_parent != nullptr) {
            logRecursive(organism->m_parent);
        }

#ifdef DEBUG_EXTREME
        std::cout << "[APGG LOD] " << "Payoff: " << organism->m_payoff << " " << organism->getDebugString() << std::endl;
#endif
        m_archiver->archive(organism);*/
    }

    void LOD::logIterative(pOrganism& organism) {
        /*std::vector<pOrganism> organisms;

        while (organism->m_parent != nullptr) {
#ifdef DEBUG_EXTREME
            std::cout << "[APGG LOD] " << "Payoff: " << organism->m_payoff << " " << organism->getDebugString() << std::endl;
#endif
            organisms.push_back(organism);
            organism = organism->m_parent;
        }

        for (auto it = organisms.end(); it != organisms.begin(); --it) {
            if (*it != nullptr) {
                m_archiver->archive(*it);
            }
        }*/
    }


    void LOD::logTop(Grid& grid) {
        Organism* organism =& grid.getTopOrganism();

        while (organism->m_parent != nullptr) {
            m_archiver->archive(organism);
            organism = organism->m_parent;
        }
    }

    void LOD::cleanup(Grid& grid)
    {
    }

    void LOD::setArchiver(std::unique_ptr<LODArchiver>& archiver) {
        m_archiver = std::move(archiver);
    }

}
