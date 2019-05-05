#include "Grid.h"



Grid::Grid()
{
	m_grid.reserve(Config::getInstance().width * Config::getInstance().height);
	for (unsigned int i = 0; i < Config::getInstance().width * Config::getInstance().height; i++)
	{
		m_grid.emplace_back(std::make_unique<Organism>());
	}
}

pOrganism& Grid::getOrganism(const unsigned int x, const unsigned int y)
{
	//assert(x < width&&"X out of bounds!");
	//assert(y < height&&"Y out of bounds!");

	unsigned int index = x + y * Config::getInstance().width;
	return m_grid[index];

}

pOrganism& Grid::getOrganism(const int index)
{
//	assert(index < Config::getInstance().width* Config::getInstance().height&&"Index out of bounds!");
	return m_grid[index];
}

const std::vector<rOrganism> Grid::data()
{
    return m_gridCache;
}

void Grid::data(const std::vector<pOrganism> data)
{
  // m_grid = data;
}

void Grid::rebuildCache()
{
    m_gridCache.clear();
    m_gridCache.reserve(size());
    for (auto &ptr : m_grid) {
        m_gridCache.push_back(std::ref(*ptr));
    }
}

void Grid::sortByFitness()
{
	std::sort(m_grid.begin(), m_grid.end(), [](const pOrganism &a, const pOrganism &b) {
		return a->m_payoff > b->m_payoff;
	});
}

unsigned int Grid::size()
{
    return static_cast<unsigned int>(m_grid.size());
}

