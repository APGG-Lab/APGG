#include "Organism.h"

Organism::Organism()
{
	for (auto & genome : m_genomes)
	{
		genome.setValue(static_cast <float> (rand()) / static_cast <float> (RAND_MAX));
	}
}

bool Organism::operator>(const Organism & rhs) const
{
	return m_fitness > rhs.m_fitness;
}

bool Organism::operator<(const Organism & rhs) const
{
	return m_fitness < rhs.m_fitness;
}

