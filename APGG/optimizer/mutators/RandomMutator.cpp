#include "RandomMutator.h"

void APGG::RandomMutator::mutate(Grid& grid, const std::unordered_set<unsigned int>& selection)
{
    for (const unsigned int& index : selection) {
        if (m_mutationRate < getRandomFloat()) {
            continue;
        }

        Organism& organism = grid[index];

        //@todo: replace with % m_genomes.size()
        organism.m_genomes[getRandomNumber() % 2].shuffle();
    }
}

void APGG::RandomMutator::configure(Config& config)
{
	m_mutationRate = stof(config.getValue("mutationRate"));
}
