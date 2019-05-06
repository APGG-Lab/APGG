#include "ProportionateRepupoluator.h"


void ProportionateRepupoluator::repopulate(std::shared_ptr<Grid>& grid, std::vector<rOrganism>& selection)
{
	float min = grid->getMinPayoff();
	float max = grid->getMaxPayoff();
	for (rOrganism& organism : selection)
	{
		rOrganism donatorOrganism = grid->getRandomOrganism(selection);

        float payoff = donatorOrganism.get().getNormalizedPayoff(min, max);
		if (payoff >= getRandomFloat())
		{
			organism.get().m_genomes = donatorOrganism.get().m_genomes;
		}
	}
}