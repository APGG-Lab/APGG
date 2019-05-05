#pragma once
#include <cassert>

#include "Organism.h"
#include <algorithm>


class Grid
{
public:
	Grid();

    pOrganism& getOrganism(const unsigned int x, const unsigned int y);
    pOrganism& getOrganism(const int index);
    const std::vector<rOrganism> data();
    void data(const std::vector<pOrganism> data);
    void rebuildCache();
	void sortByFitness();
    unsigned int size();
private:
	std::vector<pOrganism> m_grid;
    std::vector<rOrganism> m_gridCache;
};

