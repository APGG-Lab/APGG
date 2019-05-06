#include "ProportionateRepupoluator.h"


void ProportionateRepupoluator::repopulate(std::shared_ptr<Grid>& grid, std::vector<pOrganism>& selection)
{
	float min = grid->getMinPayoff();
	float max = grid->getMaxPayoff();
	for (pOrganism& organism : selection)
	{
		pOrganism donatorOrganism = grid->getRandomOrganism(selection);
		//todo use blacklist
		float payoff = donatorOrganism->getNormalizePayoff(min, max);
		if (payoff >= getRandomFloat())
		{
			organism->m_genomes = donatorOrganism->m_genomes;
		}
	}
}