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

std::vector<pOrganism> Group::data() const
{
    return m_group;
}

void Group::data(const std::vector<pOrganism> data)
{
    m_group = data;
}

unsigned int Group::size()
{
    return static_cast<unsigned int>(m_group.size());
}
