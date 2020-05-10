#include "RandomRepopulator.h"

namespace APGG {
    void repopulate(Grid& grid, std::unordered_set<GridIndex>& selection);
    void configure(Config& config);

    void RandomRepopulator::repopulate(Grid& grid, std::unordered_set<GridIndex>& selection)
    {
        for (const GridIndex& index : selection) {
            grid[index].m_genomes[0].shuffle();
            grid[index].m_genomes[1].shuffle();
        }
    }
	void RandomRepopulator::configure(Config& config)
	{
	}
}