#pragma once
#include "Organism.h"
#include <numeric>
class Group
{
private:
    std::vector<pOrganism> m_group;
    std::array<unsigned int, 4> m_count;
public:
    Group(const unsigned int size);
    void add(const pOrganism& organism);
    std::vector<pOrganism> data();
    void data(const std::vector<pOrganism> data);
    unsigned int size();
    ~Group();
};

