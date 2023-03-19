#pragma once
#include "Organism.h"

namespace APGG {

    //TODO: move to definitions.h
    typedef uint16_t GridIndex;

    /**
    * Keeps information about a group of agents that interact with each other during an experiment. 
    * Relation to agents is kept only as an index to the position in the grid to minimize memory and maximize performance. 
    * Provides basic functions to access agents and modify their faction classification.
    */
    class Group
    {
    private:
        std::vector<GridIndex> m_group;
        std::array<unsigned int, Faction::Count> m_count;
    public:
        void resize(const unsigned int size);
        std::vector<GridIndex>::iterator begin();
        std::vector<GridIndex>& data();

        GridIndex& operator[](const unsigned int index);
        unsigned int size();

        std::array<unsigned int, Faction::Count>& getFactionCounter();
        void increaseFactionCount(const Faction faction);
        void clearFactionCount();
    };

}