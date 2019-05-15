#pragma once
#include <cassert>

#include "Organism.h"
#include <algorithm>

namespace APGG {

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
        rOrganism& getRandomOrganism();
        rOrganism& getRandomOrganism(const std::vector<rOrganism>& blacklist);
		int getID();
		unsigned int getGeneration() const { return m_generation; } ;
		void setGeneration(const unsigned int generation) { m_generation = generation; };
    private:
        std::vector<pOrganism> m_grid;
        std::vector<rOrganism> m_gridCache;
		int m_IDCounter = 0;
		unsigned int m_generation = 0;
    };

}