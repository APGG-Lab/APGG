#include "Mutator.h"

void APGG::Mutator::setMutationRate(const float rate)
{
    m_motationRate = rate/100.0f; //TODO: Possibly move this somewhere else
}