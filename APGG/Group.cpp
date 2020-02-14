#include "Group.h"
#include "Group.h"
#include "Group.h"
#include "Group.h"

namespace APGG {

    void Group::resize(const unsigned int size)
    {
        m_group.resize(size);
    }

    std::vector<unsigned int>::iterator Group::begin()
    {
        return m_group.begin();
    }

    std::vector<unsigned int>& Group::data()
    {
        return m_group;
    }

    unsigned int Group::size()
    {
        return static_cast<unsigned int>(m_group.size());
    }

}