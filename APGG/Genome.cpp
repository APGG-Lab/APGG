#include "Genome.h"



Genome::Genome()
{
}

float Genome::getValue() const
{
	return m_value;
}

void Genome::setValue(const float value)
{
	m_value = value;
}

