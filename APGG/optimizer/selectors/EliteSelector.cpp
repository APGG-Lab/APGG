#include "EliteSelector.h"

namespace APGG {


    EliteSelector::EliteSelector() : Selector()
    {
    }

    EliteSelector::EliteSelector(const unsigned int eliminationCount) : Selector(eliminationCount)
    {
    }

    std::vector<rOrganism> EliteSelector::select(std::shared_ptr<Grid>& grid)
    {
        m_selection.clear();

        auto gridData = grid->data();

        grid->sortByFitness();
        for (unsigned int i = grid->size() - 1; i > grid->size() - 1 - m_eliminationCount; i--) {
            m_selection.emplace_back(gridData[i]);
        }

        return m_selection;
    }

	void EliteSelector::configure(Config& config)
	{
		m_eliminationCount = stoul(config.getValue("eliminationCount"));
	}

}