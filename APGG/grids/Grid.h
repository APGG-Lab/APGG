#pragma once
#include <cassert>
#include <algorithm>
#include <stack>
#include <unordered_set>

#include "../Organism.h"
#include "../Configurable.h"
#include "../Group.h"

namespace APGG {

    class Grid : public Configurable
    {
    protected:
        unsigned int m_width = 0;
        unsigned int m_height = 0;
        unsigned int m_totalSize = 0;
        unsigned int m_generation = 0;

        std::vector<Organism> m_grid;
        std::vector<GridIndex> m_gridKeys;

        //ID of the organism
        unsigned int m_IDCounter = 0;

        unsigned int m_groupSize;
        std::vector<Group> m_groups;

    public:
        Grid();

        //Empty implementation to avoid errors when we use the base class
        virtual void configure(Config& config);
        void setGeneration(const unsigned int generation);
        unsigned int size() const;
        std::vector<Organism>& getData();
        unsigned int getGeneration() const;
        Organism& operator[](const GridIndex index);
        Organism& get(const GridIndex index);
        std::pair<float, float> getMinMaxPayoff();
        GridIndex getRandomOrganismIndex();
        GridIndex getRandomOrganismIndex(const std::unordered_set<GridIndex>& blacklist);

        unsigned int getID();

        std::array<unsigned int, 4> getFactionCount();
        std::vector<GridIndex> sortByFitness(const bool desc = false);
        Organism& getTopOrganism();
    
        std::vector<Group>& getGroups();
        std::vector<GridIndex>& getGridKeys();

        //Empty implementation to avoid errors when we use the base class
        virtual void generateGroups();


        static std::unique_ptr<Grid> Create(Config& config);
    };
}