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
              << "\tNum Defectors: " << (Config::getInstance().width * Config::getInstance().height - m_cooperation)
              << "\tPercentage: " << m_fitness
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
    std::cout << "[APGG] Init ...";

    m_clock_start = m_clock_now = m_clock_last = HighResClock::now();
    m_exponent = 1;
    m_cooperation = 0;
    m_fitness = 0.0f;

    {
        //Generate new filename
        std::time_t t = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        std::tm buf;
        localtime_s(&buf, &t);
        std::stringstream ssTp;
        ssTp << std::put_time(&buf, "experiments/score_%Y_%m_%d_%H_%M_%S.csv");
        myfile.open(ssTp.str());
    }

    {
        //Show timedelta for init
        m_clock_now = HighResClock::now();
        fsec fs = m_clock_now - m_clock_last;
        m_clock_last = m_clock_now;
        ms timeDelta = std::chrono::duration_cast<ms>(fs);
        std::cout << "took " << timeDelta.count() << " ms" << std::endl;
    }
}

void World::Tick()
{
    m_cooperation = 0;
    m_fitness = 0.0f;

	for (int i = 0; i < Config::getInstance().width * Config::getInstance().height; i++)
	{
		float cooperationValue = getRandomFloat();

		if (m_grid.getOrganism(i).m_genomes[0].getValue() > 0.5)
		{
			m_cooperation++;
			m_grid.getOrganism(i).m_cooperated = true;
		}
		else
		{
			m_grid.getOrganism(i).m_cooperated = false;
		}
	}

	m_fitness = static_cast<float>(m_cooperation) / (Config::getInstance().width* Config::getInstance().height);

	// calculate adaption
	for (int i = 0; i < Config::getInstance().width * Config::getInstance().height; i++)
	{
		if (m_grid.getOrganism(i).m_cooperated)
		{
			m_grid.getOrganism(i).m_fitness = m_fitness;
		}
		else
		{
			m_grid.getOrganism(i).m_fitness = m_fitness + 1;

		}
	}
	World::Archive(m_fitness, m_cooperation, (Config::getInstance().width * Config::getInstance().height - m_cooperation));
    printStatus();
}

void World::Fini()
{
    fsec fs = m_clock_now - m_clock_start;
    ms timeDelta = std::chrono::duration_cast<ms>(fs);
    std::cout << "[APGG] Fini (took " << timeDelta.count() << " ms)" << std::endl;

	myfile.close();
}

void World::Evolve()
{
	m_grid.sortByFitness();
	for (unsigned int i = Config::getInstance().width * Config::getInstance().height - 1;
		i > Config::getInstance().width* Config::getInstance().height - Config::getInstance().eliminationCount; i--) {
		m_grid.getOrganism(i).m_genomes[0].shuffle();
	}
	m_generation++;
}

void World::Archive(float fitness, int cooperation, int defectors)
{
	myfile << m_generation << ";" << fitness << ";" << cooperation << ";" << defectors << std::endl;
}
