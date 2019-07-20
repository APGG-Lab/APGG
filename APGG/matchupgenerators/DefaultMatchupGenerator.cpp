#include "DefaultMatchupGenerator.h"

namespace APGG {

    void DefaultMatchupGenerator::generateGroups()
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

	void DefaultMatchupGenerator::configure(Config& config)
	{
		setGroupSize(stoul(config.getValue("groupSize", "10")));
	}
}