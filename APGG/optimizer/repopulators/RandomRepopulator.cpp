#include "RandomRepopulator.h"

void RandomRepopulator::repopulate(std::shared_ptr<Grid>& grid, std::vector<pOrganism>& selection)
{
    for (pOrganism& organism : selection) {
        organism->m_genomes[0].shuffle();
        organism->m_genomes[1].shuffle();
        organism->m_payoff = 1.0f;
    }
}
