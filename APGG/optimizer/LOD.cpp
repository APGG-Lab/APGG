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

            if (!organism.m_children2.empty()) {
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

        organism.copyTo2(organismCopy); //Copy all values to the new organism
        organismCopy->m_generation = grid.getGeneration();

        // Only root nodes shoudln't have a parent. IF should be true
        // in 99% of the time
        if (organism.m_parent2 != nullptr) { 
            // Replace the original organism with the new copy.
            // Therefore we've to replace the organism in the parent
            // organsim as well
            organismCopy->m_parent2->removeChild2(&organism);
            organismCopy->m_parent2->addChild2(organismCopy);
        }
        else if(organism.ID > 1024) {
            int test = 0;
        }

        for (Organism* child : organism.m_children2) {
            // We also have to change the parent of the children 
            // with the new copy
            child->m_parent2 = organismCopy;
        }

        //Cleanup the organism
        organism.m_parent2 = nullptr;
        organism.clearChildren2();
        organism.ID = -1;
        organism.m_status = STATUS_DELETED;
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


        parent->removeChild(organism);
        
        if (parent->m_status != STATUS_CLONE) {
            DEBUG_MSG("LOD Cleanup: organism is not a clone " + organism->getDebugString());
            return;
        }

        removeAndCleanupChildLists(parent);
        parent.reset();

        DEBUG_MSG("LOD Cleanup: done " + organism->getDebugString());
    }

    void LOD::removeAndCleanupChildLists2(Organism& organism)
    {

            Organism* parent = nullptr;
            Organism* organismPtr = &organism;

            // Use loop instead of a recursive function, because a recursive
            // function can crash the software, when the tree is too high
            while (organismPtr->m_children2.empty()) {  //Loop through until we find a organism with a child

                if (organismPtr->m_parent2 == nullptr) {
                    //Only root elements have a nullptr as m_parent
                    DEBUG_MSG("LOD Cleanup: found root organism " + organism->getDebugString());
                    return;
                }

                //Remove organismPtr from child/parent tree
                parent = organismPtr->m_parent2;
                parent->removeChild2(organismPtr);
                organismPtr->m_parent2 == nullptr;

                //Parent element is still in grid. We can't remove it. Stop loop here!
                if (organismPtr->m_parent2->m_status != STATUS_CLONE) {
                    return;
                }
                
                // Organism is a clone (only true for the second iteration of this loop
                // first iteration is always an organism on the grid.
                // If it's a copy, we have to remove it, to avoid a fast growing memory leak
                if (organismPtr->m_status == STATUS_CLONE) {
                    delete organismPtr;
                }

                //Swap actual organism with parent organism
                organismPtr = parent;

            }
    }

    void LOD::validate(const pOrganism& organism) {
        //Something is terribly wrong if you see these messages in your console
        if (organism->m_children.size() > 0) {
            DEBUG_MSG("LOD Validator: Dead Organism has children " + organism->getDebugString());
        }
        if (organism->m_parent != nullptr) {
            DEBUG_MSG("LOD Validator: Dead Organism has a parent " + organism->getDebugString());
        }
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

    void LOD::logIterative2(Organism* organism)
    {
        std::vector<Organism*> organisms;

        while (organism->m_parent2 != nullptr) {
            organisms.push_back(organism);
            organism = organism->m_parent2;
            std::cout << organism->ID << std::endl;
        }

        std::cout << organisms.size() << std::endl;

        int test = 0;

    }

    void LOD::logTop() {
       /* m_grid->sortByFitness();
        pOrganism topOragnism = m_grid->data()[0].get().getPtr();
        logIterative(topOragnism);*/
    }

    void LOD::setArchiver(std::unique_ptr<LODArchiver>& archiver) {
        //m_archiver = std::move(archiver);
    }

}
