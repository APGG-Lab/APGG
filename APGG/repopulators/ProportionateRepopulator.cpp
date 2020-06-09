#include "ProportionateRepopulator.h"

namespace APGG {

    void ProportionateRepupoluator::repopulate(Grid& grid, std::unordered_set<GridIndex>& selection)
    {
        const auto minMaxPayoff = grid.getMinMaxPayoff();

        for (const GridIndex deadOrganismIndex : selection) {
            GridIndex parentIndex;

            int i = 0;
            float payoff = -10000.0f;

            do {
                parentIndex = grid.getRandomOrganismIndex(selection);
                payoff = grid[parentIndex].getNormalizedPayoff(minMaxPayoff.first, minMaxPayoff.second);

                if (minMaxPayoff.first == minMaxPayoff.second) {
                    //Min == Max => Difference equals 0
                    //Avoid infinite loop
                    break;
                }

                //break when we get payoff >= rand or when we failed 3 times.
            } while (payoff <= getRandomFloat() && i++ < 25); 

            Organism& deadOrganism = grid[deadOrganismIndex];


            //LOD STUFF
            grid[parentIndex].addChild(&deadOrganism);
            deadOrganism.m_parent = &grid[parentIndex];

            //Normal Generation Stuff
            deadOrganism.m_genomes = grid[parentIndex].m_genomes;
            deadOrganism.m_status = Status::Original;

#ifdef __DEBUG1
            deadOrganism.m_generation = grid.getGeneration();
            //Assign new ID
            deadOrganism.ID = grid.getID();
#endif


            DEBUG_MSG("Repopulator: created offspring " + deadOrganism.getDebugString());
            DEBUG_MSG("Repopulator: from parent " + grid[parentOrganismIndex].getDebugString());
        }
    }
	void ProportionateRepupoluator::configure(Config& config)
	{
	}
}