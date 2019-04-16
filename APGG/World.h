#pragma once

#include "Grid.h"
#include <iostream>
#include <fstream>

class World
{
public:
	World();
	~World();
	void Tick();
	void Evolve();
	void Archive(float fitness, int cooperation, int defectors);
	std::ofstream myfile;
	Grid m_grid;
	int m_generation = 0;
};

