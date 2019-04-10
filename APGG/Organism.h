#pragma once

#include "Genome.h"
#include <array>

constexpr unsigned int nrGenomes = 1;

class Organism
{
public:
	Organism();

	std::array<Genome, nrGenomes> m_genomes;

	bool m_cooperated;
	float m_fitness = 1;

	bool operator>(const Organism &rhs) const;
	bool operator<(const Organism &rhs) const;

};

