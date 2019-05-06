#pragma once
#include <cassert>

#include "Organism.h"
#include <algorithm>


class Grid
{
public:
	Grid();

    pOrganism getOrganism(const unsigned int x, const unsigned int y);
    pOrganism getOrganism(const int index);
    std::vector<pOrganism> data();
    void data(const std::vector<pOrganism> data);
	void sortByFitness();
	float getMinPayoff();
	float getMaxPayoff();
    unsigned int size();
	pOrganism getRandomOrganism() const;
	pOrganism getRandomOrganism(const std::vector<pOrganism>& blacklist) const;
private:
	std::vector<pOrganism> m_grid;
};

