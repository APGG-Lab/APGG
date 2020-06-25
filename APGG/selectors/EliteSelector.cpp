#include "EliteSelector.h"

namespace APGG {


    std::unordered_set<GridIndex>& EliteSelector::select(Grid& grid)
    {

        m_selection.clear();

        std::vector<GridIndex> gridKeys = grid.sortByFitness(true);

        for (unsigned int i = 0; i < m_eliminationCount; i++) 
        {
            m_selection.insert(gridKeys[i]);
        }

        return m_selection;
    }

	void EliteSelector::configure(Config& config)
	{
        m_eliminationCount = stoul(config.getValue("eliminationCount"));
        const unsigned int width = stoul(config.getValue("width"));
        const unsigned int height = stoul(config.getValue("height"));
        const unsigned int totalSize = width * height;

        if (m_eliminationCount / static_cast<float>(totalSize) >= 1.0) 
        {
            std::cerr << "\n[APGG Error] EliminationCount >= size of grid";
            std::cin.get();
            std::quick_exit(1);
        }
        else if (m_eliminationCount / static_cast<float>(totalSize) > 0.9) 
        {
            std::cout << "[APGG Warning] EliminationCount is 0.9% of the grid size. It can take a while to find a good organism\n";
        }

        m_selection.reserve(m_eliminationCount);
	}

}