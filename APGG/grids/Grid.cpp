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
		    organism.ID = m_IDCounter++;
		    organism.m_generation = m_generation;
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

   // float Grid::getMinPayoff()
   //{
   //    float tempMin = std::numeric_limits<float>::max();
   //    for (const Organism& org : m_grid)
   //    {
   //        if (org->m_payoff <= tempMin)
   //            tempMin = org->m_payoff;
   //    }
   //    return tempMin;
   //}

   //float Grid::getMaxPayoff()
   //{
   //    float tempMax = std::numeric_limits<float>::min();
   //    for (const Organism& org : m_grid)
   //    {
   //        if (org->m_payoff >= tempMax)
   //            tempMax = org->m_payoff;
   //    }
   //    return tempMax;
   //}

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

 //   pOrganism& Grid::getOrganism(const unsigned int x, const unsigned int y)
 //   {
 //       //assert(x < width&&"X out of bounds!");
 //       //assert(y < height&&"Y out of bounds!");

 //       unsigned int index = x + y * m_width;
 //       return m_grid[index];

 //   }

 //   pOrganism& Grid::getOrganism(const int index)
 //   {
 //       //	assert(index < Config::getInstance().width* Config::getInstance().height&&"Index out of bounds!");
 //       return m_grid[index];
 //   }

 //   const std::vector<rOrganism> Grid::data()
 //   {
 //       return m_gridCache;
 //   }

 //   void Grid::data(const std::vector<pOrganism> data)
 //   {
 //       // m_grid = data;
 //   }

 //   void Grid::rebuildCache()
 //   {
 //       m_gridCache.clear();
 //       m_gridCache.reserve(size());
 //       for (auto &ptr : m_grid) {
 //           m_gridCache.push_back(std::ref(*ptr));
 //       }
 //   }

    void Grid::sortByFitness()
    {
        std::sort(m_grid.begin(), m_grid.end(), [](const Organism &a, const Organism &b) {
            return a.m_payoff > b.m_payoff;
        });
    }

	//unsigned int Grid::getWidth() const
	//{
	//	return m_width;
	//}

 //   unsigned int Grid::size()
 //   {
 //       return static_cast<unsigned int>(m_grid.size());
 //   }

	//unsigned int Grid::getHeight() const
	//{
	//	return m_height;
	//}



 //   rOrganism& Grid::getRandomOrganism() {
 //       int rand = getRandomNumber() % m_grid.size();
 //       return m_gridCache[rand];
 //   }

 //   rOrganism& Grid::getRandomOrganism(const std::vector<rOrganism>& blacklist) {

 //       int rand = getRandomNumber() % m_grid.size();
 //       auto& returnOrganism = m_gridCache[rand];

 //       for (const rOrganism& organism : blacklist) {
 //           if (returnOrganism.get().ID == organism.get().ID) {
 //               returnOrganism = getRandomOrganism(blacklist);
 //               break;
 //           }
 //       }

 //       //todo cool blacklist implementation;

 //       return returnOrganism;
 //   }



	//void Grid::configure(Config& config)
	//{
	//	m_width = stoul(config.getValue("width"));
	//	m_height = stoul(config.getValue("height"));


	//	m_grid.reserve(m_width * m_height);
	//	for (unsigned int i = 0; i < m_width * m_height; i++)
	//	{
	//		auto organism = std::make_unique<Organism>();
	//		organism->ID = getID();
	//		organism->m_generation = getGeneration();
	//		m_grid.emplace_back(std::move(organism));

	//	}
	//}

}