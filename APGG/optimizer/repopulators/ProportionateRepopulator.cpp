#include "ProportionateRepopulator.h"

namespace APGG {

    void ProportionateRepupoluator::repopulate(std::shared_ptr<Grid>& grid, std::vector<rOrganism>& selection)
    {
        float min = grid->getMinPayoff();
        float max = grid->getMaxPayoff();

      // grid->refCountCheck();

        rOrganism rParent = grid->getRandomOrganism(selection);
       // grid->refCountCheck();

        for (rOrganism& deadOrganism : selection)
        {
			float payoff = std::numeric_limits<float>::min();
			
			while (payoff <= getRandomFloat()) {
                rParent = grid->getRandomOrganism(selection);

                if (min == max) {
                    //Min == Max => Difference equals 0
                    break;
                }

				payoff = rParent.get().getNormalizedPayoff(min, max);
			}

         //   grid->refCountCheck();


            pOrganism ptr = deadOrganism.get().getPtr();


			////Set child in parent
			//Set parent in child
            if (deadOrganism.get().m_parent != nullptr) {
                deadOrganism.get().m_parent->removeChild(ptr);
            }

            if (!deadOrganism.get().m_children.empty()) {
                int test = 0;
            }
            deadOrganism.get().m_parent = nullptr;


            deadOrganism.get().m_parent = rParent.get().getPtr();
            deadOrganism.get().m_parent->addChild(ptr);
            ptr.reset();

            //grid->refCountCheck();

			//Copy genomes && reset organism
            deadOrganism.get().m_genomes = rParent.get().m_genomes;
            deadOrganism.get().m_status = STATUS_ORIGINAL;
			//pDeadOrganism->m_history += "(R," + std::to_string(grid->getGeneration()) + "," + std::to_string(pDeadOrganism->ID) + ")|";
            deadOrganism.get().clearChilds();
            deadOrganism.get().m_generation = grid->getGeneration();

			//Assign new ID
			deadOrganism.get().ID = grid->getID();

           // grid->refCountCheck();

            DEBUG_MSG("Repopulator: created offspring " + deadOrganism.get().getDebugString());
            DEBUG_MSG("Repopulator: from parent " + rParent.get().getDebugString());
        }
    }
}