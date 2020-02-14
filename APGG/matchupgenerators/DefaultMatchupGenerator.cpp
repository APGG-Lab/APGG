#include "DefaultMatchupGenerator.h"


namespace APGG {

    void DefaultMatchupGenerator::generateGroups()
    {
        //Fill vector with grid key numbers and shuffle them
        std::vector<unsigned int> gridKeys(m_grid->size()); // vector with 1024 uints.
        std::iota(std::begin(gridKeys), std::end(gridKeys), 0); // Fill with 0, 1, ..., 99.
        std::shuffle(gridKeys.begin(), gridKeys.end(), std::mt19937());

        //determine number of groups
        int numberOfGroups = (gridKeys.size() - 1) / m_groupSize + 1;

        m_groups.resize(numberOfGroups);

        // each iteration of this loop process next set of n elements
        // and store it in a vector at i'th index in vec
        for (int i = 0; i < numberOfGroups; ++i) {
            // get range for next set of n elements
            auto start_itr = std::next(gridKeys.cbegin(), i * m_groupSize);
            auto end_itr = std::next(gridKeys.cbegin(), i * m_groupSize + m_groupSize);

            // allocate memory for the sub vector
            m_groups[i].resize(m_groupSize);

            // code to handle the last sub-vector as it might
            // contain less elements (unused, because totalSize%groupSize = 0)
            //    if (i * m_groupSize + m_groupSize > gridKeys.size()) {
            //       end_itr = gridKeys.end();
            //       m_groupsNew[i].reserve(gridKeys.size() - i * m_groupSize);
            //    }

            // copy elements from the input range to the sub-vector
            std::copy(start_itr, end_itr, m_groups[i].begin());
        }
    }
}