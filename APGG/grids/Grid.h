#pragma once
#include <cassert>
#include <algorithm>
#include <stack>

#include "../Organism.h"
#include "../Configurable.h"

namespace APGG {

    class Grid : public Configurable
    {
    public:
        Grid();

        pOrganism& getOrganism(const unsigned int x, const unsigned int y);
        pOrganism& getOrganism(const int index);
        const std::vector<rOrganism> data();
        void data(const std::vector<pOrganism> data);
        void rebuildCache();
        void sortByFitness();
		unsigned int getWidth() const;
		unsigned int getHeight() const;
        float getMinPayoff();
        float getMaxPayoff();
        unsigned int size();
        rOrganism& getRandomOrganism();
        rOrganism& getRandomOrganism(const std::vector<rOrganism>& blacklist);
		int getID();
		unsigned int getGeneration() const { return m_generation; } ;
		void setGeneration(const unsigned int generation) { m_generation = generation; };
        void wipe() {
            m_gridCache.clear();
            std::list<pOrganism> myList;

            for (auto& organism : m_grid) {
                //recursiveDelete(organism, myList);
				iterativeDelete(organism, myList);
            }
			std::cout << myList.size() << std::endl;
            for (auto& organism : myList) {
                for (auto& child : organism->m_children) {
                    child.reset();
                }
                organism->clearChildren();
                organism->m_parent.reset();
                organism->m_parent = nullptr;
            }
            myList.clear();
            m_grid.clear();
        }

        void recursiveDelete(pOrganism& organism, std::list<pOrganism>& list) {
            organism->clearChildren();
            list.push_back(organism);
            if (organism->m_parent != nullptr ) {
                    recursiveDelete(organism->m_parent, list);
            }
        }

		void iterativeDelete(pOrganism& startOrganism, std::list<pOrganism>& list) {
			auto organism = startOrganism;
			auto organismParent = startOrganism->m_parent;
			while (organismParent != nullptr)
			{
				organism = organismParent;
				organism->clearChildren();
				list.push_back(organism);

				organismParent = organism->m_parent;
				organism->m_parent = nullptr;
			}
		}

		void configure(Config& config);
    protected:
        std::vector<pOrganism> m_grid;
        std::vector<rOrganism> m_gridCache;
		int m_IDCounter = 0;
		unsigned int m_generation = 0;
		unsigned int m_width;
		unsigned int m_height;
    };

}