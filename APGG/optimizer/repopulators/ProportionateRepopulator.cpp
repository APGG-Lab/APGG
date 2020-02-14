#include "ProportionateRepopulator.h"

namespace APGG {

    void ProportionateRepupoluator::repopulate(Grid& grid, std::unordered_set<unsigned int>& selection) 
    {
        auto minMaxPayoff = grid.getMinMaxPayoff();

        unsigned int parentOrganismIndex = grid.getRandomOrganismIndex(selection);

        for (const unsigned int deadOrganismIndex : selection) {
            float payoff = std::numeric_limits<float>::min();

            while (payoff <= getRandomFloat()) {
                parentOrganismIndex = grid.getRandomOrganismIndex(selection);

                payoff = grid[parentOrganismIndex].getNormalizedPayoff(minMaxPayoff.first, minMaxPayoff.second);

                if (minMaxPayoff.first == minMaxPayoff.second || payoff == 0) {
                    //Min == Max => Difference equals 0
                    //Avoid infinite loop
                    break;
                }
            }





            Organism& deadOrganism = grid[deadOrganismIndex];

            deadOrganism.clearChildren();

            //LOD STUFF
            //  deadOrganism.get().m_parent = rParent.get().getPtr();
            // deadOrganism.get().m_parent->addChild(ptr);
            //  deadOrganism.m_parent = grid[parentOrganismIndex]
            //  ptr.reset();


            //Normal Generation Stuff
            deadOrganism.m_genomes = grid[parentOrganismIndex].m_genomes;
            deadOrganism.m_status = STATUS_ORIGINAL;
            deadOrganism.m_mutated = false;
            deadOrganism.m_generation = grid.getGeneration();

            //Assign new ID
          //  deadOrganism.ID = grid.getID();


            DEBUG_MSG("Repopulator: created offspring " + deadOrganism.get().getDebugString());
            DEBUG_MSG("Repopulator: from parent " + rParent.get().getDebugString());
        }

   //     rOrganism rParent = grid->getRandomOrganism(selection);

   //     for (rOrganism& deadOrganism : selection)
   //     {
			//float payoff = std::numeric_limits<float>::min();
			//
			//while (payoff <= getRandomFloat()) {
   //             rParent = grid->getRandomOrganism(selection);

   //             if (min == max || payoff == 0) {
   //                 break;
   //             }

			//	payoff = rParent.get().getNormalizedPayoff(min, max);
			//}

   //         pOrganism ptr = deadOrganism.get().getPtr();

   //         deadOrganism.get().m_parent = rParent.get().getPtr();
   //         deadOrganism.get().m_parent->addChild(ptr);
   //         ptr.reset();


			////Copy genomes && reset organism
   //         deadOrganism.get().m_genomes = rParent.get().m_genomes;
   //         deadOrganism.get().m_status = STATUS_ORIGINAL;
   //         deadOrganism.get().m_mutated = false;
   //         deadOrganism.get().clearChildren();
   //         deadOrganism.get().m_generation = grid->getGeneration();

			////Assign new ID
			//deadOrganism.get().ID = grid->getID();


   //         DEBUG_MSG("Repopulator: created offspring " + deadOrganism.get().getDebugString());
   //         DEBUG_MSG("Repopulator: from parent " + rParent.get().getDebugString());
    //    }
    }
	void ProportionateRepupoluator::configure(Config& config)
	{
	}
}