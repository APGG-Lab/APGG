#include "Organism.h"


bool Organism::assignProfession(const float cooperationValue)
{
    m_cooperated = m_genomes[GENOME_COOPERATION].getValue() >= cooperationValue;
    return m_cooperated;
}

bool Organism::assignMorals(const float moralValue)
{
    m_moralist = m_genomes[GENOME_MORALS].getValue() >= moralValue;
    return m_moralist;
}

Faction Organism::assignFaction()
{
    assignProfession(getRandomFloat());
    assignMorals(getRandomFloat());

    if (m_cooperated && !m_moralist) m_faction = FACTION_COOPERATOR;
    else if (m_cooperated && m_moralist) m_faction = FACTION_MORALIST;
    else if (!m_cooperated && !m_moralist) m_faction = FACTION_DEFECTOR;
    else m_faction = FACTION_IMMORALIST;

    return m_faction;
}

Faction Organism::getFaction()
{
    return m_faction;
}

void Organism::setPayoff(const float payoff)
{
    m_payoff = payoff;

    if (m_payoff < 0) {
        m_payoff = 0;
    }
}

float Organism::getNormalizedPayoff(const float min, const float max)
{
	auto payoff =  (m_payoff + std::abs(min)) / (max + std::abs(min));
    return payoff;
}
