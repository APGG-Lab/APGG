#include "Organism.h"

Organism::Organism()
{
}

bool Organism::operator>(const Organism & rhs) const
{
	return m_payoff > rhs.m_payoff;
}

bool Organism::operator<(const Organism & rhs) const
{
	return m_payoff < rhs.m_payoff;
}

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

void Organism::setPayoff(const float payoff)
{
    m_payoff = payoff;

    if (m_payoff < 0) {
        m_payoff = 0;
    }
}

