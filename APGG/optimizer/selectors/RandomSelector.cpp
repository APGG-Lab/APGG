#include "RandomSelector.h"

namespace APGG {

    RandomSelector::RandomSelector() : Selector()
    {
    }

    RandomSelector::RandomSelector(const unsigned int eliminationCount) : Selector(eliminationCount)
    {
    }

    std::unordered_set<unsigned int> RandomSelector::select(Grid& grid)
    {
        std::unordered_set<unsigned int> selection(m_eliminationCount);


        while (selection.size() < m_eliminationCount) {
            int randomIndex = getRandomNumber() % grid.size();

            // The index already exists in our selection. Try again
            if (selection.find(randomIndex) != selection.end()) {
                continue;
            }

            selection.emplace(randomIndex);
        }

        return selection;
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