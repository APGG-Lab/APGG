#pragma once
#include "Organism.h"
#include <numeric>

namespace APGG {

    class Group
    {
    private:
        std::vector<rOrganism> m_group;
        std::array<unsigned int, 4> m_count;
    public:
        Group(const unsigned int size);
        void add(const rOrganism organism);
        std::vector<rOrganism> data() const;
        void data(const std::vector<rOrganism> data);
        unsigned int size();
        ~Group();
    };

}