#include "ProportionateRepopulator.h"

namespace APGG {

    void ProportionateRepupoluator::repopulate(std::shared_ptr<Grid>& grid, std::vector<rOrganism>& selection)
    {
        float min = grid->getMinPayoff();
        float max = grid->getMaxPayoff();

        rOrganism rParent = grid->getRandomOrganism(selection);

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

            pOrganism ptr = deadOrganism.get().getPtr();

            deadOrganism.get().m_parent = rParent.get().getPtr();
            deadOrganism.get().m_parent->addChild(ptr);
            ptr.reset();


			//Copy genomes && reset organism
            deadOrganism.get().m_genomes = rParent.get().m_genomes;
            deadOrganism.get().m_status = STATUS_ORIGINAL;
            deadOrganism.get().m_mutated = false;
            deadOrganism.get().clearChildren();
            deadOrganism.get().m_generation = grid->getGeneration();

			//Assign new ID
			deadOrganism.get().ID = grid->getID();


            DEBUG_MSG("Repopulator: created offspring " + deadOrganism.get().getDebugString());
            DEBUG_MSG("Repopulator: from parent " + rParent.get().getDebugString());
        }
    }
}