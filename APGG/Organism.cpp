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

bool Organism::assignProfession(const float cooperationValue)
{
    m_cooperated = m_genomes[GENOME_COOPERATION].getValue() >= cooperationValue;
    return m_cooperated;
}

