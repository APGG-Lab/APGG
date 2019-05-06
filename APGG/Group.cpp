#include "Group.h"

namespace APGG {


    Group::~Group()
    {
    }

    Group::Group(const unsigned int size)
    {
        m_group.reserve(size);
    }

    void Group::add(const rOrganism organism)
    {
        m_group.push_back(organism);
    }

    std::vector<rOrganism> Group::data() const
    {
        return m_group;
    }

    void Group::data(const std::vector<rOrganism> data)
    {
        m_group = data;
    }


    unsigned int Group::size()
    {
        return static_cast<unsigned int>(m_group.size());
    }

}