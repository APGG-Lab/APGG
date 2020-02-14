#pragma once
#include "Organism.h"

namespace APGG {

    class Group
    {
    private:
        std::vector<unsigned int> m_group;
        std::array<unsigned int, Faction::Count> m_count;
    public:
        void resize(const unsigned int size);
        std::vector<unsigned int>::iterator begin();
        std::vector<unsigned int>& data();
        unsigned int size();

        std::array<unsigned int, Faction::Count>& getFactionCounter();
        void increaseFactionCount(const Faction faction);
        void clearFactionCount();
    };

}