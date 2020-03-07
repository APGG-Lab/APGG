#pragma once
#include <cassert>
#include <algorithm>
#include <stack>
#include <unordered_set>

#include "../Organism.h"
#include "../Configurable.h"
#include "../Group.h"

namespace APGG {

    typedef uint16_t GridIndex;

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

        unsigned int m_groupSize;
        std::vector<Group> m_groups;

    public:
        Grid();
        virtual void configure(Config& config) = 0;
        void setGeneration(const unsigned int generation);
        unsigned int size() const;
        std::vector<Organism>& getData();
        unsigned int getGeneration() const;
        Organism& operator[](const GridIndex index);
        std::pair<float, float> getMinMaxPayoff();
        GridIndex getRandomOrganismIndex();
        GridIndex getRandomOrganismIndex(const std::unordered_set<GridIndex>& blacklist);

        unsigned int getID();

        std::array<unsigned int, 4> getFactionCount();
        void sortByFitness();
        Organism& getTopOrganism();
    
        std::vector<Group>& getGroups();
        virtual void generateGroups() = 0;
    };
}