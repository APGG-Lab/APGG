#include "RandomSelector.h"

namespace APGG {

    RandomSelector::RandomSelector() : Selector()
    {
    }

    RandomSelector::RandomSelector(const unsigned int eliminationCount) : Selector(eliminationCount)
    {
    }

    std::unordered_set<GridIndex>& RandomSelector::select(Grid& grid)
    {
        m_selection.clear();

        while (m_selection.size() < m_eliminationCount) {
            m_selection.emplace(grid.getRandomOrganismIndex(m_selection));
        }

        return m_selection;
    }

	void RandomSelector::configure(Config& config)
	{
		m_eliminationCount = stoul(config.getValue("eliminationCount"));
        const unsigned int width = stoul(config.getValue("width"));
        const unsigned int height = stoul(config.getValue("height"));
        const unsigned int totalSize = width * height;

        if (m_eliminationCount / static_cast<float>(totalSize) >= 1.0) {
            std::cerr << std::endl << "[APGG Error] EliminationCount >= size of grid";
            std::cin.get();
            std::quick_exit(1);
        }
        else if(m_eliminationCount / static_cast<float>(totalSize) > 0.9){
            std::cout << "[APGG Warning] EliminationCount is 0.9% of the grid size. It can take a while to find a good organism" << std::endl;
        }

        m_selection.reserve(m_eliminationCount);
	}

}