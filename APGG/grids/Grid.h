#pragma once
#include <cassert>
#include <algorithm>
#include <stack>
#include <unordered_set>

#include "../Organism.h"
#include "../Configurable.h"
namespace APGG {

    class Grid : public Configurable
    {
    protected:
        unsigned int m_width = 0;
        unsigned int m_height = 0;
        unsigned int m_totalSize = 0;
        unsigned int m_generation = 0;

        std::vector<Organism> m_grid;

        //ID of the organism
        unsigned int m_IDCounter = 0;

    public:
        Grid();
        void configure(Config& config);
        void setGeneration(const unsigned int generation);
        unsigned int size() const;
        std::vector<Organism>& getData();
        unsigned int getGeneration() const;
        Organism& operator[](unsigned int index);

        //float getMinPayoff();
        //float getMaxPayoff();
        std::pair<float, float> getMinMaxPayoff();
        unsigned int getRandomOrganismIndex();
        unsigned int getRandomOrganismIndex(const std::unordered_set<unsigned int>& blacklist);

        void test() { m_grid[0].setPayoff(1000); }
        //void Grid::configure(Config& config)
//{

//}

    //    pOrganism& getOrganism(const unsigned int x, const unsigned int y);
    //    pOrganism& getOrganism(const int index);
    //    const std::vector<rOrganism> data();
    //    void data(const std::vector<pOrganism> data);
    //    void rebuildCache();
    //    void sortByFitness();
    //    unsigned int getWidth() const;
    //    unsigned int getHeight() const;

    //    unsigned int size();
    //    rOrganism& getRandomOrganism(const std::vector<rOrganism>& blacklist);
    //   
    //    unsigned int getGeneration() const { return m_generation; };
    //    
    //    void wipe() {
    //        m_gridCache.clear();
    //        std::list<pOrganism> myList;

    //        for (auto& organism : m_grid) {
    //            //recursiveDelete(organism, myList);
    //            iterativeDelete(organism, myList);
    //        }
    //        std::cout << myList.size() << std::endl;
    //        for (auto& organism : myList) {
    //            for (auto& child : organism->m_children) {
    //                child.reset();
    //            }
    //            organism->clearChildren();
    //            organism->m_parent.reset();
    //            organism->m_parent = nullptr;
    //        }
    //        myList.clear();
    //        m_grid.clear();
    //    }

    //    void recursiveDelete(pOrganism& organism, std::list<pOrganism>& list) {
    //        organism->clearChildren();
    //        list.push_back(organism);
    //        if (organism->m_parent != nullptr) {
    //            recursiveDelete(organism->m_parent, list);
    //        }
    //    }

    //    void iterativeDelete(pOrganism& startOrganism, std::list<pOrganism>& list) {
    //        auto organism = startOrganism;
    //        auto organismParent = startOrganism->m_parent;
    //        while (organismParent != nullptr)
    //        {
    //            organism = organismParent;
    //            organism->clearChildren();
    //            list.push_back(organism);

    //            organismParent = organism->m_parent;
    //            organism->m_parent = nullptr;
    //        }
    //    }


    //}
    };
}