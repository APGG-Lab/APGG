#pragma once

#include "random.h"
#include "Config.h"

class Genome 
{
private:
	float m_value = 0.f;
public:
	Genome();
	Genome(const float value) : m_value(value) {};
	float getValue() const;
	void setValue(const float value);
	void shuffle();
};

