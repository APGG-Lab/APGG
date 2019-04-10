#pragma once
class Genome 
{
public:
	Genome();
	Genome(const float value) : m_value(value) {};

	float m_value = 0.f;
};

