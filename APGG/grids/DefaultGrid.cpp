#include "Grid.h"
#include "DefaultGrid.h"

namespace APGG {
	void DefaultGrid::generateGroups()
	{
        std::shuffle(m_gridKeys.begin(), m_gridKeys.end(), std::mt19937());


        // each iteration of this loop process next set of n elements
        // and store it in a vector at i'th index in vec
        for (int i = 0; i < numberOfGroups; ++i) {
            // get range for next set of n elements
            auto start_itr = std::next(m_gridKeys.cbegin(), i * m_groupSize);
            auto end_itr = std::next(m_gridKeys.cbegin(), i * m_groupSize + m_groupSize);

            // allocate memory for the sub vector
         //   m_groups[i].resize(m_groupSize);

            // code to handle the last sub-vector as it might
            // contain less elements (unused, because totalSize%groupSize = 0)
            //    if (i * m_groupSize + m_groupSize > m_gridKeys.size()) {
            //       end_itr = m_gridKeys.end();
            //       m_groupsNew[i].reserve(m_gridKeys.size() - i * m_groupSize);
            //    }

            // copy elements from the input range to the sub-vector
            std::copy(start_itr, end_itr, m_groups[i].begin());
        }
	}
    void DefaultGrid::configure(Config& config)
    {
        m_width = stoi(config.getValue("width"));
        m_height = stoi(config.getValue("height"));
        m_totalSize = m_width * m_height;

        if (m_grid.size() % stoi(config.getValue("groupSize")) != 0) {
            std::cerr << "\n[APGG Error] invalid group size. Gridsize (height*width) % Groupsize must be 0";
            std::cin.get();
            std::quick_exit(1);
        };

        m_grid.reserve(m_totalSize);
        for (unsigned int i = 0; i < m_width * m_height; i++)
        {
            Organism organism(m_genomeNumber);
#ifdef __DEBUG1
            organism.ID = m_IDCounter++;
            organism.m_generation = m_generation;
#endif
            m_grid.emplace_back(std::move(organism));
        }
            


        //from DefaultMatchupGenerator
        m_groupSize = stoul(config.getValue("groupSize", "10"));

        //Fill vector with grid key numbers and shuffle them
        m_gridKeys.resize(m_totalSize); // vector with 1024 uints.
        std::iota(std::begin(m_gridKeys), std::end(m_gridKeys), 0); // Fill with 0, 1, ..., 99.


        //determine number of groups
        numberOfGroups = (static_cast<int>(m_gridKeys.size()) - 1) / m_groupSize + 1;

        m_groups.resize(numberOfGroups);

        for (int i = 0; i < numberOfGroups; ++i) {
            // allocate memory for the sub vector
            m_groups[i].resize(m_groupSize);
        }
    }
}