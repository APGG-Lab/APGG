#include "Grid.h"



Grid::Grid()
{
}

Organism & Grid::getOrganism(const unsigned int x, const unsigned int y)
{
	//assert(x < width&&"X out of bounds!");
	//assert(y < height&&"Y out of bounds!");

	unsigned int index = x + y * width;
	return m_grid[index];
}

Organism & Grid::getOrganism(const int index)
{
	assert(index < width*height&&"Index out of bounds!");
	return m_grid[index];
}

void Grid::sortByFitness()
{
	std::sort(m_grid.begin(), m_grid.end(), [](const Organism &a, const Organism &b) {
		return a > b;
	});
}

