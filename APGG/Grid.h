#pragma once
#include <cassert>

#include "Organism.h"
#include <algorithm>


class Grid
{
public:
	Grid();
	
	Organism & getOrganism(const unsigned int x, const unsigned int y);
	Organism & getOrganism(const int index);
    std::vector<Organism> data();
    void data(const std::vector<Organism>& data);
	void sortByFitness();
private:
	std::vector<Organism> m_grid;
};

