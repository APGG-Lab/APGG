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
        std::pair<float, float> getMinMaxPayoff();
        unsigned int getRandomOrganismIndex();
        unsigned int getRandomOrganismIndex(const std::unordered_set<unsigned int>& blacklist);

        unsigned int getID();

        std::array<unsigned int, 4> getFactionCount();
        void sortByFitness();
        Organism& getTopOrganism();
    //    unsigned int getWidth() const;
    //    unsigned int getHeight() const;
    };
}