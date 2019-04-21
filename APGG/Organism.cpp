#include "Organism.h"

Organism::Organism()
{
}

bool Organism::operator>(const Organism & rhs) const
{
	return m_fitness > rhs.m_fitness;
}

bool Organism::operator<(const Organism & rhs) const
{
	return m_fitness < rhs.m_fitness;
}

