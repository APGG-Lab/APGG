#include "RandomSelector.h"

RandomSelector::RandomSelector() : Selector()
{
}

RandomSelector::RandomSelector(const unsigned int eliminationCount) : Selector(eliminationCount)
{
}

std::vector<rOrganism> RandomSelector::select(std::shared_ptr<Grid>& grid)
{
    m_selection.clear();
	while (m_selection.size() < m_eliminationCount) {
		m_selection.push_back(grid->getRandomOrganism( m_selection));
	}

    return m_selection;
}
