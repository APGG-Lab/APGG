#include "Group.h"



Group::~Group()
{
}

Group::Group(const unsigned int size)
{
    m_group.reserve(size);
}

void Group::add(const pOrganism& organism)
{
    m_group.push_back(organism);
}

std::vector<pOrganism> Group::data()
{
    return m_group;
}

void Group::data(const std::vector<pOrganism> data)
{
    m_group = data;
}

void Group::predacheNumbers()
{
}

unsigned int Group::getNumCooperators()
{
    unsigned int counter = 0;
    for (const pOrganism& organism : m_group) {
        counter += organism->m_cooperated;
    }
    return counter;
}

unsigned int Group::getNumDefectors()
{
    unsigned int counter = 0;
    for (const pOrganism& organism : m_group) {
        counter += !organism->m_cooperated;
    }
    return counter;
}

unsigned int Group::getNumMoralists()
{
    unsigned int counter = 0;
    for (const pOrganism& organism : m_group) {
        counter += organism->m_moralist;
    }
    return counter;
}

unsigned int Group::getNumImmoralists()
{
    unsigned int counter = 0;
    for (const pOrganism& organism : m_group) {
        counter += !organism->m_moralist;
    }
    return counter;
}

unsigned int Group::size()
{
    return static_cast<unsigned int>(m_group.size());
}
