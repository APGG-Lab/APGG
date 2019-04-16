#pragma once

#include "Organism.h"
#include <algorithm>
#include <cassert>

constexpr unsigned int width = 32;
constexpr unsigned int height = 32;

class Grid
{
public:
	Grid();
	
	Organism & getOrganism(const unsigned int x, const unsigned int y);
	Organism & getOrganism(const int index);
	void sortByFitness();
private:
	std::array<Organism, width*height> m_grid;


};

