#include "World.h"



World::World()
{
}

void World::Init()
{
    std::cout << "[APGG] Init" << std::endl;
}

void World::Tick()
{
	unsigned int cooperation = 0;
	
	for (int i = 0; i < width * height; i++) 
	{
		float cooperationValue = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);

		if (m_grid.getOrganism(i).m_genomes[0].m_value > 0.5)
		{
			cooperation++;
			m_grid.getOrganism(i).m_cooperated = true;
		}
		else
		{
			m_grid.getOrganism(i).m_cooperated = false;
		}
	}
	int defectors = width * height - cooperation;
	float percentage = static_cast<float>(cooperation) / static_cast<float>(width*height);
	//std::cout << " Num Cooperators: " << cooperation 
	//		  << "\tNum Defectors: " <<defectors
	//	      << "\tPercentage: " << percentage*100 << std::endl;

	float fitness = percentage;

	// calculate adaption
	for (int i = 0; i < width * height; i++)
	{
		if (m_grid.getOrganism(i).m_cooperated)
		{
			m_grid.getOrganism(i).m_fitness =  fitness;
		}
		else
		{
			m_grid.getOrganism(i).m_fitness =  fitness + 1;

		}
	//	std::cout << m_grid.getOrganism(i).m_fitness << std::endl;
	}

}

void World::Fini()
{
    std::cout << "[APGG] Fini" << std::endl;
}

void World::Evolve()
{
	m_grid.sortByFitness();
	unsigned int eliminateCount = 20;
	for (int i = width * height - 1; i > width*height - eliminateCount; i--) {
		float cooperationValue = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);

		m_grid.getOrganism(i).m_genomes[0] = cooperationValue;
	}
	m_generation++;
}


