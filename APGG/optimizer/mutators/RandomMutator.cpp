#include "RandomMutator.h"

void APGG::RandomMutator::mutate(const std::vector<rOrganism>& selection)
{
    for (rOrganism org : selection)
    {
        if (m_motationRate > getRandomFloat())
        {
            org.get().m_genomes[getRandomNumber() % 2].shuffle();
            org.get().m_mutated = true;
        }
    }
}
