#include "LOD.h"

namespace APGG {

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
