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

            if (!deadOrganism.m_children2.empty() || deadOrganism.m_parent2 != nullptr) {
                int test = 0;
            }

            deadOrganism.clearChildren2();

            //LOD STUFF
            grid[parentOrganismIndex].addChild2(&deadOrganism);
            deadOrganism.m_parent2 = &grid[parentOrganismIndex];

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
            deadOrganism.ID = grid.getID();


            DEBUG_MSG("Repopulator: created offspring " + deadOrganism.getDebugString());
            DEBUG_MSG("Repopulator: from parent " + grid[parentOrganismIndex].getDebugString());
        }
    }
	void ProportionateRepupoluator::configure(Config& config)
	{
	}
}