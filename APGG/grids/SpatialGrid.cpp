#include "Grid.h"
#include "SpatialGrid.h"

namespace APGG {

    GridIndex SpatialGrid::wrap(int x,  int y)
    {

        if (x < 0) {
            x = m_width - 1;
        }
        else if (x >= m_width) {
            x = 0;
        }

        if (y < 0) {
            y = m_height - 1;
        }
        else if (y >= m_height) {
            y = 0;
        }

        return static_cast<GridIndex>((y * m_width) + x);
    }

    void SpatialGrid::generateGroups()
	{
        if (m_built) {
            return;
        }

        for (int y = 0; y < m_height; y++) {
            for (int x = 0; x < m_width; x++) {
                const GridIndex index = (m_width * y) + x;

                //Group group;
                m_groups[index].data() = {
                                wrap(x,y-1),
                    wrap(x-1,y), index, wrap(x+1,y),
                               wrap(x,y+1)
                };
            }
        }

        m_built = true;
	}

    void SpatialGrid::configure(Config& config)
    {
        m_width = stoi(config.getValue("width"));
        m_height = stoi(config.getValue("height"));
        m_totalSize = m_width * m_height;

        m_grid.reserve(m_totalSize);
        for (unsigned int i = 0; i < m_width * m_height; i++)
        {
            Organism organism;
#ifdef __DEBUG1
            organism.ID = m_IDCounter++;
            organism.m_generation = m_generation;
#endif
            m_grid.emplace_back(std::move(organism));
        }
            
        m_groupSize = 5;

        //Fill vector with grid key numbers and shuffle them
        m_gridKeys.resize(m_totalSize); // vector with 1024 uints.
        std::iota(std::begin(m_gridKeys), std::end(m_gridKeys), 0); // Fill with 0, 1, ..., 99.


        //determine number of groups
        numberOfGroups = (m_gridKeys.size() - 1) / m_groupSize + 1;

        m_groups.resize(m_totalSize);

        for (int i = 0; i < numberOfGroups; ++i) {
            // allocate memory for the sub vector
            m_groups[i].resize(5);
        }
    }
}