#pragma once
#include <array>
#include <memory>
#include "Genome.h"

constexpr unsigned int nrGenomes = 2;

enum GenomeNames { GENOME_COOPERATION = 0, GENOME_MORALS, GENOME_HISTORY1, GENOME_HISTORY2, GENOME_HISTORY3} ;

class Organism
{
public:
	Organism();

	std::array<Genome, nrGenomes> m_genomes;

	bool m_cooperated;
    bool m_moralist;
    //@todo startvalue?
	float m_payoff = 100;

	bool operator>(const Organism &rhs) const;
	bool operator<(const Organism &rhs) const;

    bool assignProfession(const float cooperationValue);
    bool assignMorals(const float moralValue);
    void setPayoff(const float payoff);
};

typedef std::shared_ptr<Organism> pOrganism;

