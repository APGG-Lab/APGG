#include "Grid.h"



Grid::Grid()
{
	m_grid.reserve(Config::getInstance().width * Config::getInstance().height);
	for (int i = 0; i < Config::getInstance().width * Config::getInstance().height; i++)
	{
		m_grid.push_back(Organism());
	}
}

Organism & Grid::getOrganism(const unsigned int x, const unsigned int y)
{
	//assert(x < width&&"X out of bounds!");
	//assert(y < height&&"Y out of bounds!");

	unsigned int index = x + y * Config::getInstance().width;
	return m_grid[index];
}

Organism & Grid::getOrganism(const int index)
{
	assert(index < Config::getInstance().width* Config::getInstance().height&&"Index out of bounds!");
	return m_grid[index];
}

std::vector<Organism> Grid::data()
{
    return m_grid;
}

void Grid::data(const std::vector<Organism>& data)
{
    m_grid = data;
}

void Grid::sortByFitness()
{
	std::sort(m_grid.begin(), m_grid.end(), [](const Organism &a, const Organism &b) {
		return a > b;
	});
}

