#include "Mutator.h"

void APGG::Mutator::setMutationRate(const float rate)
{
    m_motationRate = rate/100.0f; //TODO: Possibly move this somewhere else
}

void APGG::Mutator::mutate(const std::vector<rOrganism>& selection)
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
