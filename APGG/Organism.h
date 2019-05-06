#pragma once
#include <array>
#include <memory>
#include "Genome.h"

constexpr unsigned int nrGenomes = 2;

enum GenomeNames { GENOME_COOPERATION = 0, GENOME_MORALS, GENOME_HISTORY1, GENOME_HISTORY2, GENOME_HISTORY3} ;
enum Faction { FACTION_COOPERATOR = 0, FACTION_DEFECTOR, FACTION_MORALIST, FACTION_IMMORALIST };

class Organism
{
public:
	std::array<Genome, nrGenomes> m_genomes;
    unsigned int ID;
	bool m_cooperated;
    bool m_moralist;
    Faction m_faction;
    //@todo startvalue?
	float m_payoff = 1;

    bool assignProfession(const float cooperationValue);
    bool assignMorals(const float moralValue);
    Faction assignFaction();
    Faction getFaction();
	float getNormalizedPayoff(const float min, const float max);

    void setPayoff(const float payoff);
};

typedef std::unique_ptr<Organism> pOrganism;
typedef std::reference_wrapper<Organism> rOrganism;

