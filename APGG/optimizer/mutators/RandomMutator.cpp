#include "RandomMutator.h"

void APGG::RandomMutator::mutate(const std::vector<rOrganism>& selection)
{
    for (rOrganism org : selection)
    {
        if (m_mutationRate > getRandomFloat())
        {
            org.get().m_genomes[getRandomNumber() % 2].shuffle();
            org.get().m_mutated = true;
        }
    }
}

void APGG::RandomMutator::configure(Config& config)
{
	m_mutationRate = stof(config.getValue("mutationRate"));
}
