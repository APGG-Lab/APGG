#include "World.h"



void World::printStatus()
{

    if (m_generation % m_exponent != 0) {
        return;
    }

    m_clock_now = HighResClock::now();
    fsec fs = m_clock_now - m_clock_last;
    m_clock_last = m_clock_now;
    ms timeDelta = std::chrono::duration_cast<ms>(fs);

    std::cout << "Generation:" << m_generation
              << "\tNum Cooperators: " << m_cooperation
              << "\tNum Defectors: " << (width * height - m_cooperation)
              << "\tPercentage: " << m_percentage
              << "\ttook: " << timeDelta.count() << " ms" << std::endl;

    if (m_generation >= m_exponent * 10) {
        //Only increase the exponent, when m_generation reaches m_exponent
        //otherwise we'll print only at 1,10,100,1000,...

        m_exponent *= 10;
    }
}

World::World()
{
}

void World::Init()
{
    std::cout << "[APGG] Init" << std::endl;

    m_clock_start = m_clock_now = m_clock_last = HighResClock::now();
    m_exponent = 1;
    m_cooperation = 0;
    m_percentage = 0.0f;
}

void World::Tick()
{
    m_cooperation = 0;
    m_percentage = 0.0f;

	for (int i = 0; i < width * height; i++) 
	{
		float cooperationValue = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);

		if (m_grid.getOrganism(i).m_genomes[0].m_value > 0.5)
		{
			m_cooperation++;
			m_grid.getOrganism(i).m_cooperated = true;
		}
		else
		{
			m_grid.getOrganism(i).m_cooperated = false;
		}
	}
	int defectors = width * height - m_cooperation;
	m_percentage = static_cast<float>(m_cooperation) / static_cast<float>(width*height);


	float fitness = m_percentage;

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
    printStatus();
}

void World::Fini()
{
    fsec fs = m_clock_now - m_clock_start;
    ms timeDelta = std::chrono::duration_cast<ms>(fs);
    std::cout << "[APGG] Fini (took " << timeDelta.count() << " ms)" << std::endl;
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


