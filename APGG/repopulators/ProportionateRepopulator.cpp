#include "ProportionateRepopulator.h"

namespace APGG {

    void ProportionateRepupoluator::repopulate(Grid& grid, std::unordered_set<GridIndex>& selection)
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


            //LOD STUFF
            grid[parentOrganismIndex].addChild(&deadOrganism);
            deadOrganism.m_parent = &grid[parentOrganismIndex];

            //Normal Generation Stuff
            deadOrganism.m_genomes = grid[parentOrganismIndex].m_genomes;
            deadOrganism.m_status = Status::Original;
            deadOrganism.m_payoff = 0.0f;

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