#include "Group.h"
#include "Group.h"
#include "Group.h"
#include "Group.h"

namespace APGG {

    void Group::resize(const unsigned int size)
    {
        m_group.resize(size);
    }

    std::vector<GridIndex>::iterator Group::begin()
    {
        return m_group.begin();
    }

    std::vector<GridIndex>& Group::data()
    {
        return m_group;
    }

    GridIndex& Group::operator[](const unsigned int index)
	{
        return m_group[index];
	}

	unsigned int Group::size()
    {
        return static_cast<unsigned int>(m_group.size());
    }

    std::array<unsigned int, Faction::Count>& Group::getFactionCounter()
    {
        return m_count;
    }

    void Group::increaseFactionCount(const Faction faction)
    {
        m_count[faction]++;
    }

    void Group::clearFactionCount()
    {
        std::fill(std::begin(m_count), std::end(m_count), 0);
    }

}