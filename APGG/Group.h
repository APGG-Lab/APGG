#pragma once
#include "Organism.h"

namespace APGG {

    //TODO: move to definitions.h
    typedef uint16_t GridIndex;


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