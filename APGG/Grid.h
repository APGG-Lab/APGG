#pragma once
#include <cassert>

#include "Organism.h"
#include <algorithm>

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

