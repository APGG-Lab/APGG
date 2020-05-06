#include "SpatialRepopulator.h"

namespace APGG {

    void SpatialRepopulator::repopulate(Grid& grid, std::unordered_set<GridIndex>& selection)
    {
        auto fitnessRanking = grid.sortByFitness();

        for (const GridIndex deadOrganismIndex : selection) {

            unsigned int y = deadOrganismIndex / m_width;
            unsigned int x = deadOrganismIndex - (m_width * y);

            //TODO: replace this with a vector for radius repopulation?
            GridIndex neighbors[4] = { wrap(x - 1, y), wrap(x + 1, y), wrap(x, y - 1), wrap(x, y + 1) };

            GridIndex parentOrganismIndex;
            
            //this is expected to find the fittest parentOrganismIndex at some point
            for (GridIndex organismIndex : fitnessRanking)
            {
                if (neighbors[0] == organismIndex)
                {
                    parentOrganismIndex = organismIndex;
                    break;
                }
                if (neighbors[1] == organismIndex)
                {
                    parentOrganismIndex = organismIndex;
                    break;
                }
                if (neighbors[2] == organismIndex)
                {
                    parentOrganismIndex = organismIndex;
                    break;
                }
                if (neighbors[3] == organismIndex)
                {
                    parentOrganismIndex = organismIndex;
                    break;
                }
            }

            Organism& deadOrganism = grid[deadOrganismIndex];


            //LOD STUFF
            grid[parentOrganismIndex].addChild(&deadOrganism);
            deadOrganism.m_parent = &grid[parentOrganismIndex];

            //Normal Generation Stuff
            deadOrganism.m_genomes = grid[parentOrganismIndex].m_genomes;
            deadOrganism.m_status = Status::Original;

#ifdef __DEBUG1
            deadOrganism.m_generation = grid.getGeneration();
            //Assign new ID
            deadOrganism.ID = grid.getID();
#endif


            DEBUG_MSG("Repopulator: created offspring " + deadOrganism.getDebugString());
            DEBUG_MSG("Repopulator: from parent " + grid[parentOrganismIndex].getDebugString());
        }
    }

    void SpatialRepopulator::configure(Config& config)
    {
        m_width = stoi(config.getValue("width"));
        m_height = stoi(config.getValue("height"));
        m_totalSize = m_width * m_height;
    }

    GridIndex SpatialRepopulator::wrap(int x, int y)
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
}