#include "World.h"



void World::printStatus()
{
    if (m_generation % m_exponent != 0 && !Config::getInstance().showAllGenerations) {
        return;
    }

    m_clock_now = HighResClock::now();
    fsec fs = m_clock_now - m_clock_last;
    m_clock_last = m_clock_now;
    ms timeDelta = std::chrono::duration_cast<ms>(fs);
    float size = static_cast<float>(Config::getInstance().width) * Config::getInstance().height;

    std::cout << "Generation:" << m_generation
              << "\tC(%): " << m_countC << "(" << m_countC/size*100 << ")"
              << "\tD(%): " << m_countD << "(" << m_countD /size * 100 << ")"
              << "\tM(%): " << m_countM << "(" << m_countM/size * 100 << ")"
              << "\tI(%): " << m_countI << "(" << m_countI /size * 100 << ")"
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
    m_countM = m_countC = m_countI = m_countD = 0;
    m_fitness = 0.0f;

    m_grid = std::make_shared<Grid>();

    
    m_matchupGenerator.setGroupSize(Config::getInstance().groupSize);
    m_matchupGenerator.setGrid(m_grid);

    auto logSuffix = Config::getInstance().logSuffix;
    auto folderName = Config::getInstance().folderName;

    m_archiver.setFolderName(Config::getInstance().folderName);
    m_archiver.applyTimestampToFolder(false);
    m_archiver.setFileStuffix(Config::getInstance().logSuffix);
    m_archiver.applyTimestampToFile(true);
    m_archiver.open();

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
    m_countM = m_countC = m_countI = m_countD = 0;
    int localCooperation = 0;
    float localPayoff = 0;
    m_matchupGenerator.generateGroups();

    std::vector<Group> groups = m_matchupGenerator.getGroups();

    //@todo for(group:groups) could be better. 
    for (int i = 0; i < groups.size(); i++) {
        localCooperation = 0;
        for (pOrganism organism : *groups[i].data()) {
            float cooperationValue = getRandomFloat();
            float moralValue = getRandomFloat();
            bool coop = organism->assignProfession(cooperationValue);
            bool moral = organism->assignMorals(moralValue);
            if (coop && moral) m_countM++;
            else if (coop && !moral) m_countC++;
            else if (!coop && moral) m_countI++;
            else m_countD++;
        }

        int numDefectors = groups[i].getNumDefectors();
        float punishmentCost = numDefectors * Config::getInstance().punishmentCost;
        for (pOrganism organism : *groups[i].data()) {
            if (!organism->m_moralist) continue;
            organism->m_payoff -= punishmentCost;
        }

        int numMoralists = groups[i].getNumMoralists();
        float punishmentFine = numMoralists * Config::getInstance().punishmentFine;
        for (pOrganism organism : *groups[i].data()) {
            if (!organism->m_cooperated) continue;
            organism->m_payoff -= punishmentFine;
        }

        localPayoff = Config::getInstance().synergyFactor * 
            static_cast<float>(groups[i].getNumCooperators()) / (groups[i].data()->size());

        // calculate adaption
        for (pOrganism& organism : *groups[i].data()) {
            if (organism->m_cooperated)
            {
                organism->m_payoff += localPayoff - 1;
             //   organism->setPayoff(localPayoff);
            }
            else
            {
                organism->m_payoff += localPayoff;
              //  organism->setPayoff(localPayoff + 1);
            }
        //    std::cout << organism->m_payoff << std::endl;

        }
    }

   // m_fitness = static_cast<float>(m_cooperation) / (Config::getInstance().width * Config::getInstance().height);
    if (Config::getInstance().archiveData) {
        m_archiver.archive(m_generation, m_countC, m_countD, m_countM, m_countI);
    }
    printStatus();
}

void World::Fini()
{
    fsec fs = m_clock_now - m_clock_start;
    ms timeDelta = std::chrono::duration_cast<ms>(fs);
    std::cout << "[APGG] Fini (took " << timeDelta.count() << " ms)" << std::endl;

    m_archiver.close();
}

void World::Evolve()
{
	m_grid->sortByFitness();
	for (unsigned int i = Config::getInstance().width * Config::getInstance().height - 1;
		i > Config::getInstance().width* Config::getInstance().height - Config::getInstance().eliminationCount; i--) {
		m_grid->getOrganism(i)->m_genomes[0].shuffle();
        m_grid->getOrganism(i)->m_genomes[1].shuffle();
        m_grid->getOrganism(i)->m_payoff = 100.0f;
	}
	m_generation++;
}

void World::Archive(float fitness, int cooperation, int defectors)
{
	myfile << m_generation << ";" << fitness << ";" << cooperation << ";" << defectors << std::endl;
}
