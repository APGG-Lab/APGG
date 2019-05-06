#include "RandomRepopulator.h"

namespace APGG {

    void RandomRepopulator::repopulate(std::shared_ptr<Grid>& grid, std::vector<rOrganism>& selection)
    {
        for (rOrganism& organism : selection) {
            organism.get().m_genomes[0].shuffle();
            organism.get().m_genomes[1].shuffle();
            organism.get().m_payoff = 1.0f;
        }
    }
}