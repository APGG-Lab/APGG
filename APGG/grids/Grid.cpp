#include "Grid.h"

#include "DefaultGrid.h"
#include "SpatialGrid.h"

namespace APGG {

    enum class GridType : unsigned long { Default = 0, Spatial, Count };

    Grid::Grid()
    {
    }


    void Grid::configure(Config& config)
    {
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

	Organism& Grid::operator[](const GridIndex index)
    {
        return m_grid[index];
	}

	Organism& Grid::get(const GridIndex index)
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

   GridIndex Grid::getRandomOrganismIndex()
   {
       GridIndex rand = static_cast<GridIndex>(getRandomNumber() % m_grid.size());
       return rand;
   }

   GridIndex Grid::getRandomOrganismIndex(const std::unordered_set<GridIndex>& blacklist)
   {
       GridIndex rand = getRandomOrganismIndex();
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

    std::vector<GridIndex> Grid::sortByFitness(const bool desc)
    {
        //Avoid sorting the original one, because we may need the exact position
        std::vector<GridIndex> gridKeyCopy = m_gridKeys;

        if (!desc) {
            //Low to High
            std::sort(gridKeyCopy.begin(), gridKeyCopy.end(), [this](const GridIndex& a, const GridIndex& b) {
                return m_grid[a].m_payoff < m_grid[b].m_payoff;
                });
        }
        else {
            //High to Low
            std::sort(gridKeyCopy.begin(), gridKeyCopy.end(), [this](const GridIndex& a, const GridIndex& b) {
                return m_grid[a].m_payoff > m_grid[b].m_payoff;
                });
        }


        return gridKeyCopy;
    }

    Organism& Grid::getTopOrganism()
    {
        std::vector<GridIndex> m_gridKeys;
        //Fill vector with grid key numbers and shuffle them
        m_gridKeys.resize(m_grid.size()); // vector with 1024 uints.

        std::sort(m_gridKeys.begin(), m_gridKeys.end(), [this](const unsigned int& a1, const unsigned int& a2) {
            return m_grid[a1].m_payoff > m_grid[a2].m_payoff;
            });

        return m_grid[m_gridKeys[0]];
    }

    std::vector<Group>& Grid::getGroups()
    {
        return m_groups;
    }

    std::vector<GridIndex>& Grid::getGridKeys()
    {
        return m_gridKeys;
    }

    void Grid::generateGroups()
    {
    }

	std::unique_ptr<Grid> Grid::Create(Config& config)
	{
        GridType gridType = static_cast<GridType>(stoul(config.getValue("gridType", "0")));

        if (gridType >= GridType::Count) {
            std::cerr << std::endl << "[APGG Error] invalid grid type. gridType must be < " << static_cast<int>(GridType::Count);
            std::cin.get();
            std::quick_exit(1);
        }

        std::unique_ptr<Grid> grid;

        switch (gridType) {
        case GridType::Default:
            return std::make_unique<DefaultGrid>();
        default:
        case GridType::Spatial:
            return std::make_unique<SpatialGrid>();
        }
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