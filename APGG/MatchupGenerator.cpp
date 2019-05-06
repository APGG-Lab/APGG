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

    void MatchupGenerator::generateGroups()
    {
        m_groups.clear();

        std::vector<rOrganism> gridData = m_grid->data();
        std::shuffle(gridData.begin(), gridData.end(), std::mt19937());

        for (unsigned int i = 0; i < gridData.size(); i += m_groupSize) {
            Group group(m_groupSize);

            for (unsigned int j = 0; j < m_groupSize; j++) {
                group.add(gridData[i + j]);
            }

            ////@todo use std::move or std::copy
            ////auto iterator = gridData.begin();
            ////std::move(iterator + i, iterator + i + m_groupSize, group);

            m_groups.emplace_back(group);
        }
    }

}