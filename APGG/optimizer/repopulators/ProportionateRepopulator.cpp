#include "ProportionateRepopulator.h"

namespace APGG {

    void ProportionateRepupoluator::repopulate(std::shared_ptr<Grid>& grid, std::vector<rOrganism>& selection)
    {
        float min = grid->getMinPayoff();
        float max = grid->getMaxPayoff();
        for (rOrganism& deadOrganism : selection)
        {
			pOrganism pDeadOrganism = deadOrganism.get().getPtr();

			float payoff = std::numeric_limits<float>::min();
			pOrganism pParent;
			while (payoff <= getRandomFloat()) {
				rOrganism rParent = grid->getRandomOrganism(selection);
				pParent = rParent.get().getPtr();

				if (min == max) {
					//Min == Max => Difference equals 0
					break;
				}

				payoff = pParent->getNormalizedPayoff(min, max);
			}

#ifdef DEBUG_EXTREME
            assert(pParent->ID != pDeadOrganism->ID && "repopulate SAME ID FOR PARENT AND CHILD");
            assert(pParent.get() != pDeadOrganism.get() && "repopulate SAME PTR FOR PARENT AND CHILD");
#endif

			//Set child in parent
			pParent->m_children.push_back(pDeadOrganism);
			//Set parent in child
			pDeadOrganism->m_parent = pParent;

			//Copy genomes && reset organism
			pDeadOrganism->m_genomes = pParent->m_genomes;
			pDeadOrganism->m_status = STATUS_OFFSPRING;
			//pDeadOrganism->m_history += "(R," + std::to_string(grid->getGeneration()) + "," + std::to_string(pDeadOrganism->ID) + ")|";
			pDeadOrganism->m_children.clear();
			pDeadOrganism->m_generation = grid->getGeneration();

			//Assign new ID
			pDeadOrganism->ID = grid->getID();

#ifdef DEBUG_EXTREME
            std::cout << "Repopulator: created offspring " << pDeadOrganism->ID << " ParentPTR: " << pDeadOrganism->m_parent.get() << " ID:" << pDeadOrganism->getParentID() << std::endl;
            std::cout << "Repopulator: from " << pParent->ID << " ParentPTR: " << pParent->m_parent.get() << " ID:" << pParent->getParentID() << std::endl;
#endif
        }
    }
}