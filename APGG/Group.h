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
    std::vector<pOrganism>* data();
    void data(const std::vector<pOrganism> data);
    void predacheNumbers();
    unsigned int getNumCooperators();
    unsigned int getNumDefectors();
    unsigned int getNumMoralists();
    unsigned int getNumImmoralists();
    unsigned int size();
    ~Group();
};

