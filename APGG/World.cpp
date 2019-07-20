#include "World.h"


namespace APGG {

    void World::printStatus()
    {
        if (m_generation % m_exponent != 0 && !m_showAllGenerations) {
            return;
        }

        m_clock_now = HighResClock::now();
        fsec fs = m_clock_now - m_clock_last;
        m_clock_last = m_clock_now;
        ms timeDelta = std::chrono::duration_cast<ms>(fs);
        float size = static_cast<float>(m_grid->getWidth()) * m_grid->getHeight();

        std::cout << "Generation:" << m_generation
            << "\tC(%): " << m_count[FACTION_COOPERATOR] << "(" << m_count[FACTION_COOPERATOR] / size * 100 << ")"
            << "\tD(%): " << m_count[FACTION_DEFECTOR] << "(" << m_count[FACTION_DEFECTOR] / size * 100 << ")"
            << "\tM(%): " << m_count[FACTION_MORALIST] << "(" << m_count[FACTION_MORALIST] / size * 100 << ")"
            << "\tI(%): " << m_count[FACTION_IMMORALIST] << "(" << m_count[FACTION_IMMORALIST] / size * 100 << ")"
            << "\ttook: " << timeDelta.count() << " ms" << std::endl;

        if (m_generation >= m_exponent * m_consoleOutExponent) {
            //Only increase the exponent, when m_generation reaches m_exponent
            //otherwise we'll print only at 1,10,100,1000,...

            m_exponent *= m_consoleOutExponent;
        }
    }

    void World::printInitMessage()
    {
		/*
        std::cout << std::endl << "-------------------------------------------------------------------------------------------------------------------------------------" << std::endl
                  << "You're currently running " << m_archiver.getFullFilename() << " with the following parameters:" << std::endl
                  << "numGenerations - " << Config::getInstance().numGenerations << std::endl
                  << "eliminationCount - " << Config::getInstance().eliminationCount << std::endl
                  << "groupSize - " << Config::getInstance().groupSize << std::endl
                  << "width - " << Config::getInstance().width << std::endl
                  << "height - " << Config::getInstance().height << std::endl
                  << "cooperateCost - " << Config::getInstance().cooperateCost << std::endl
                  << "synergyFactor - " << Config::getInstance().synergyFactor << std::endl
                  << "punishmentCost - " << Config::getInstance().punishmentCost << std::endl
                  << "punishmentFine - " << Config::getInstance().punishmentFine << std::endl
                  << "matchupType - " << Config::getInstance().matchupType << std::endl
                  << "selectorType - " << Config::getInstance().selectorType << std::endl
                  << "repopulatorType - " << Config::getInstance().repopulatorType << std::endl
                  << "gridType - " << Config::getInstance().gridType << std::endl
                  << "payoffType - " << Config::getInstance().payoffType << std::endl
                  << "mutatorType - " << Config::getInstance().mutatorType << std::endl
                  << "mutationRate - " << Config::getInstance().mutationRate << "%" << std::endl
                  << "showAllGenerations - " << Config::getInstance().showAllGenerations << std::endl
                  << "archiveData - " << Config::getInstance().archiveData << std::endl
                  << "visualize - " << Config::getInstance().visualize << std::endl
                  << "folderName - " << Config::getInstance().folderName << std::endl
                  << "logSuffix - " << Config::getInstance().logSuffix << std::endl
                  << "timeToFile - " << Config::getInstance().timeToFile << std::endl
                  << "timeToFolder - " << Config::getInstance().timeToFolder << std::endl
                  << "consoleOutExponent - " << Config::getInstance().consoleOutExponent << std::endl
                  << "-------------------------------------------------------------------------------------------------------------------------------------" << std::endl << std::endl;
    */
	}

    World::World()
    {
    }

    void World::Init(Config& config)
    {
        std::cout << "[APGG] Init ...";

        m_clock_start = m_clock_now = m_clock_last = HighResClock::now();
        m_exponent = 1;
        std::fill(std::begin(m_count), std::end(m_count), 0);

        m_grid = std::make_shared<Grid>();
		m_grid->configure(config);
        m_grid->rebuildCache();

        if (m_grid->size() % stoul(config.getValue("groupSize")) != 0) {
            std::cerr << std::endl << "[APGG Error] invalid group size. Gridsize (height*width) % Groupsize must be 0";
            std::cin.get();
            std::quick_exit(1);
        }


        {
            m_matchupGenerator.configure(config);
            m_matchupGenerator.setGrid(m_grid);
        }

        {
			m_archiver.configure(config);
            m_archiver.open();
        }

        {
			m_payoffCalculator.configure(config);
        }

        m_optimizer.setGrid(m_grid);
		m_optimizer.configure(config);

        {
            std::unique_ptr<LODArchiver> lodArchiver = std::make_unique<LODArchiver>();
			lodArchiver->configure(config);

            lodArchiver->open();
            m_lod = std::make_shared<LOD>();
            m_lod->setGrid(m_grid);
            m_lod->setArchiver(lodArchiver);

            m_optimizer.setLOD(m_lod);
        }

		{
			ConfigArchiver configarchiver = ConfigArchiver();
			configarchiver.configure(config);
			configarchiver.open();
			configarchiver.archive(config);
			configarchiver.close();
		}

        {
            //Show timedelta for init
            m_clock_now = HighResClock::now();
            fsec fs = m_clock_now - m_clock_last;
            m_clock_last = m_clock_now;
            ms timeDelta = std::chrono::duration_cast<ms>(fs);
            std::cout << "took " << timeDelta.count() << " ms" << std::endl;
        }

		m_consoleOutExponent = stoul(config.getValue("consoleOutExponent"));
		m_archiveData = stoi(config.getValue("archiveData"));
		m_showAllGenerations = stoi(config.getValue("showAllGenerations"));

        printInitMessage();
    }

    void World::Tick()
    {
        std::fill(std::begin(m_count), std::end(m_count), 0);
        //int localCooperation = 0;
        //float localPayoff = 0;

        m_matchupGenerator.generateGroups();

        std::vector<Group> groups = m_matchupGenerator.getGroups();
        std::array<unsigned int, 4> factionCount;

        //@todo for(group:groups) could be better. 
        for (size_t i = 0; i < groups.size(); i++) {
            std::fill(std::begin(factionCount), std::end(factionCount), 0);

            for (rOrganism organism : groups[i].data()) {
                Faction faction = organism.get().assignFaction();
                m_count[faction]++;
                factionCount[faction]++;
            }
            m_payoffCalculator.setCounters(factionCount);
            m_payoffCalculator.calculateCosts(groups[i].size());
            m_payoffCalculator.applyPayoff(groups[i]);
        }
        if (m_archiveData) {
            m_archiver.archive(m_generation, m_count[FACTION_COOPERATOR], m_count[FACTION_DEFECTOR], m_count[FACTION_MORALIST], m_count[FACTION_IMMORALIST]);
        }
        printStatus();
    }

    void World::Fini()
    {
        m_lod->logTop();

        m_grid->wipe();

        fsec fs = m_clock_now - m_clock_start;
        ms timeDelta = std::chrono::duration_cast<ms>(fs);
        std::cout << "[APGG] Fini (took " << timeDelta.count() << " ms)" << std::endl;
        m_archiver.close();
    }

    void World::Evolve()
    {
        m_optimizer.optmize();
        m_grid->rebuildCache();

        m_generation++;
		m_grid->setGeneration(m_generation);
    }

	void World::printLOD(const pOrganism& organism)
	{
		
	}

}
