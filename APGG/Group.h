#pragma once
#include "Organism.h"
#include <numeric>
class Group
{
private:
    std::vector<pOrganism> m_group;
public:
    Group(const unsigned int size);
    void add(const pOrganism& organism);
    std::vector<pOrganism>* data();
    void data(const std::vector<pOrganism> data);
    unsigned int getNumCooperators();
    unsigned int getNumDefectors();
    unsigned int getNumMoralists();
    unsigned int getNumImmoralists();
    unsigned int size();
    ~Group();
};

