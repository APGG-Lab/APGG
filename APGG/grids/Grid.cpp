#include "Grid.h"

namespace APGG {

    Grid::Grid()
    {
    }

    void Grid::configure(Config& config)
    {
        m_width = stoi(config.getValue("width"));
	    m_height = stoi(config.getValue("height"));
        m_totalSize = m_width * m_height;

        if (m_grid.size() % stoi(config.getValue("groupSize")) != 0) {
            std::cerr << std::endl << "[APGG Error] invalid group size. Gridsize (height*width) % Groupsize must be 0";
            std::cin.get();
            std::quick_exit(1);
        };

	    m_grid.reserve(m_totalSize);
	    for (unsigned int i = 0; i < m_width * m_height; i++)
	    {
            Organism organism;
#ifdef __DEBUG1
		    organism.ID = m_IDCounter++;
		    organism.m_generation = m_generation;
#endif
		    m_grid.emplace_back(std::move(organism));
	    }
    }

    void Grid::setGeneration(const unsigned int generation)
    {
        m_generation = generation;
    }

    unsigned int Grid::size() const
    {
        return m_totalSize;
    }

    std::vector<Organism>& Grid::getData()
    {
        return m_grid;
    }

    unsigned int Grid::getGeneration() const
    {
        return m_generation;
    }

	Organism& Grid::operator[](unsigned int index)
    {
        return m_grid[index];
	}

   std::pair<float, float> Grid::getMinMaxPayoff()
   {
       auto minmax = std::minmax_element(std::begin(m_grid), std::end(m_grid),
           [](const Organism& s1, const Organism& s2) {
               return s1.m_payoff < s2.m_payoff;
           });

       return std::make_pair(minmax.first->m_payoff, minmax.second->m_payoff);
   }

   unsigned int Grid::getRandomOrganismIndex()
   {
       unsigned int rand = getRandomNumber() % m_grid.size();
       return rand;
   }

   unsigned int Grid::getRandomOrganismIndex(const std::unordered_set<unsigned int>& blacklist)
   {
       unsigned int rand = getRandomOrganismIndex();
       while (blacklist.find(rand) != blacklist.end()) {
           rand = getRandomOrganismIndex();
       }
       return rand;
   }

   unsigned int Grid::getID()
   {
       return m_IDCounter++;
   }

   std::array<unsigned int, 4> Grid::getFactionCount()
   {
       std::array<unsigned int, Faction::Count> counter = { };
       for (Organism& organism : m_grid) {
           counter[organism.getFaction()]++;
       }
       return counter;
   }

    void Grid::sortByFitness()
    {
        std::sort(m_grid.begin(), m_grid.end(), [](const Organism &a, const Organism &b) {
            return a.m_payoff > b.m_payoff;
        });
    }

    Organism& Grid::getTopOrganism()
    {
        std::vector<unsigned int> gridKeys;
        //Fill vector with grid key numbers and shuffle them
        gridKeys.resize(m_grid.size()); // vector with 1024 uints.

        std::sort(gridKeys.begin(), gridKeys.end(), [this](const unsigned int& a1, const unsigned int& a2) {
            return m_grid[a1].m_payoff > m_grid[a2].m_payoff;
            });

        return m_grid[gridKeys[0]];
    }

	//unsigned int Grid::getWidth() const
	//{
	//	return m_width;
	//}

    //unsigned int Grid::getHeight() const
    //{
    //	return m_height;
    //}
}