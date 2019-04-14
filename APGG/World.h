#pragma once

#include "Grid.h"
#include <iostream>

class World
{
public:
	World();

    void Init();
	void Tick();
    void Fini();

	void Evolve();
	Grid m_grid;
	int m_generation = 0;
};

