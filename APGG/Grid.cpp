#include "Grid.h"



Grid::Grid()
{
	m_grid.reserve(Config::getInstance().width * Config::getInstance().height);
	for (unsigned int i = 0; i < Config::getInstance().width * Config::getInstance().height; i++)
	{
        auto organism = std::make_unique<Organism>();
        organism->ID = i;
		m_grid.emplace_back(std::move(organism));

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

float Grid::getMinPayoff()
{
	float tempMin = std::numeric_limits<float>::max();
	for(pOrganism& org : m_grid)
	{ 
		if (org->m_payoff <= tempMin)
			tempMin = org->m_payoff;
	}
	return tempMin;
}

float Grid::getMaxPayoff()
{
	float tempMax = std::numeric_limits<float>::min();
	for (pOrganism& org : m_grid)
	{
		if (org->m_payoff >= tempMax)
			tempMax = org->m_payoff;
	}
	return tempMax;
}

rOrganism Grid::getRandomOrganism() const {
	int rand = getRandomNumber() % m_grid.size();
	return m_gridCache[rand];
}

rOrganism Grid::getRandomOrganism(const std::vector<rOrganism>& blacklist) const {
	
	int rand = getRandomNumber() % m_grid.size();
	auto returnOrganism = m_gridCache[rand];

	for (const rOrganism& organism : blacklist) {
		if (returnOrganism.get().ID == organism.get().ID) {
			returnOrganism = getRandomOrganism(blacklist);
			break;
		}
	}
	//todo cool blacklist implementation;

	return returnOrganism;
}