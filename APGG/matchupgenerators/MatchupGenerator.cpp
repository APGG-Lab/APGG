#include "MatchupGenerator.h"

namespace APGG {

    void MatchupGenerator::setGrid(std::shared_ptr<Grid> grid)
    {
        m_grid = grid;
    }

    void MatchupGenerator::setGroupSize(const unsigned int size)
    {
        m_groupSize = size;
        m_groups.reserve(m_groupSize);
    }

    std::vector<Group> MatchupGenerator::getGroups() const
    {
        return m_groups;
    }
}