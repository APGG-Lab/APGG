#include "EliteSelector.h"

EliteSelector::EliteSelector() : Selector()
{
}

EliteSelector::EliteSelector(const unsigned int eliminationCount) : Selector(eliminationCount)
{
}

std::vector<pOrganism> EliteSelector::select(std::shared_ptr<Grid>& grid)
{
    m_selection.clear();

    grid->sortByFitness();
    for (unsigned int i = grid->size() - 1; i > grid->size() - 1 - Config::getInstance().eliminationCount; i--) {
        m_selection.push_back(grid->data()[i]);
    }

    return m_selection;
}
