#pragma once
#include <array>

#include "Genome.h"

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

