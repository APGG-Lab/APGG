#pragma once
#include <array>
#include <memory>
#include "Genome.h"

constexpr unsigned int nrGenomes = 1;

enum GenomeNames { GENOME_COOPERATION = 0, GENOME_PUNISH, GENOME_HISTORY1, GENOME_HISTORY2, GENOME_HISTORY3} ;

class Organism
{
public:
	Organism();

	std::array<Genome, nrGenomes> m_genomes;

	bool m_cooperated;
	float m_fitness = 1;

	bool operator>(const Organism &rhs) const;
	bool operator<(const Organism &rhs) const;

    bool assignProfession(const float cooperationValue);

};

typedef std::shared_ptr<Organism> pOrganism;

