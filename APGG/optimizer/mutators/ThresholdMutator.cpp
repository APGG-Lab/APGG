#include "ThresholdMutator.h"

void APGG::ThresholdMutator::mutate(Grid& grid, const std::unordered_set<GridIndex>& selection)
{
    for (const GridIndex& index : selection)
    {
        if (getRandomFloat() < m_mutationRate  ) {
            continue;
        }

        for (size_t i = 0; i < grid[index].m_genomes.size(); i++) {
            float randomFloat = getRandomFloat();

            float genomeBaseValue = grid[index].m_genomes[i].getValue();

            //base - thres   <=   randomFloat   <= base + thres
            //genomeMinValue <=   randomFloat   <= genomeMaxValue
            if (genomeBaseValue - m_threshold >= randomFloat && genomeBaseValue + m_threshold <= randomFloat) {
                grid[index].m_genomes[i].setValue(randomFloat);
            }
        }
    }
}

void APGG::ThresholdMutator::configure(Config& config)
{
	m_mutationRate = stof(config.getValue("mutationRate"));
	m_threshold = stof(config.getValue("mutationThreshold", "0.2"));
}
