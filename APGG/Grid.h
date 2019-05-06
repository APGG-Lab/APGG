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
	float getMinPayoff();
	float getMaxPayoff();
    unsigned int size();
	rOrganism getRandomOrganism() const;
	rOrganism getRandomOrganism(const std::vector<rOrganism>& blacklist) const;
private:
	std::vector<pOrganism> m_grid;
    std::vector<rOrganism> m_gridCache;
};

