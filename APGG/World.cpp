#include "World.h"


namespace APGG {

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
            << "\tC(%): " << m_count[FACTION_COOPERATOR] << "(" << m_count[FACTION_COOPERATOR] / size * 100 << ")"
            << "\tD(%): " << m_count[FACTION_DEFECTOR] << "(" << m_count[FACTION_DEFECTOR] / size * 100 << ")"
            << "\tM(%): " << m_count[FACTION_MORALIST] << "(" << m_count[FACTION_MORALIST] / size * 100 << ")"
            << "\tI(%): " << m_count[FACTION_IMMORALIST] << "(" << m_count[FACTION_IMMORALIST] / size * 100 << ")"
            << "\ttook: " << timeDelta.count() << " ms" << std::endl;

        if (m_generation >= m_exponent * Config::getInstance().consoleOutExponent) {
            //Only increase the exponent, when m_generation reaches m_exponent
            //otherwise we'll print only at 1,10,100,1000,...

            m_exponent *= Config::getInstance().consoleOutExponent;
        }
    }

    void World::printInitMessage()
    {

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
    }

    World::World()
    {
    }

    void World::Init()
    {
        std::cout << "[APGG] Init ...";

        m_clock_start = m_clock_now = m_clock_last = HighResClock::now();
        m_exponent = 1;
        std::fill(std::begin(m_count), std::end(m_count), 0);

        m_grid = std::make_shared<Grid>();
        m_grid->rebuildCache();

        if (m_grid->size() % Config::getInstance().groupSize != 0) {
            std::cerr << std::endl << "[APGG Error] invalid group size. Gridsize (height*width) % Groupsize must be 0";
            std::cin.get();
            std::quick_exit(1);
        }


        {
            m_matchupGenerator.setGroupSize(Config::getInstance().groupSize);
            m_matchupGenerator.setGrid(m_grid);
        }

        {
            if (!Config::getInstance().timeToFile && !Config::getInstance().timeToFolder) {
                std::cerr << std::endl << "[APGG Warning] timeToFile disabled. You may overwrite your previous experiments";
                std::cin.get();
            }
            m_archiver.setFolderName(Config::getInstance().folderName);
            m_archiver.applyTimestampToFolder(Config::getInstance().timeToFolder);
            m_archiver.setFileStuffix(Config::getInstance().logSuffix);
            m_archiver.applyTimestampToFile(Config::getInstance().timeToFile);
            m_archiver.open();
        }

        {
            m_payoffCalculator.setCooperationCost(static_cast<float>(Config::getInstance().cooperateCost));
            m_payoffCalculator.setSynergyFactor(static_cast<float>(Config::getInstance().synergyFactor));
            m_payoffCalculator.setPunishmentBaseCost(static_cast<float>(Config::getInstance().punishmentCost));
            m_payoffCalculator.setPunishmentBaseFine(static_cast<float>(Config::getInstance().punishmentFine));
        }

        m_optimizer.setGrid(m_grid);
        {
            if (Config::getInstance().selectorType >= nSelectorTypes) {
                std::cerr << std::endl << "[APGG Error] invalid selector type. selectorType must be < " << nSelectorTypes;
                std::cin.get();
                std::quick_exit(1);
            }

            switch (Config::getInstance().selectorType) {
            case SELECTOR_ELITE:
                m_optimizer.setSelector(std::make_shared<EliteSelector>(Config::getInstance().eliminationCount));
                break;
            default:
            case SELECTOR_RANDOM:
                m_optimizer.setSelector(std::make_shared<RandomSelector>(Config::getInstance().eliminationCount));
                break;
            }
        }
        {
            if (Config::getInstance().repopulatorType >= nRepopulatorTypes) {
                std::cerr << std::endl << "[APGG Error] invalid repopulator type. repopulatorType must be < " << nRepopulatorTypes;
                std::cin.get();
                std::quick_exit(1);
            }

            switch (Config::getInstance().repopulatorType) {
            case REPOPULATOR_RANDOM:
                m_optimizer.setRepopulator(std::make_shared<RandomRepopulator>());
                break;
            default:
            case REPOPULATOR_PROPORTIONATE:
                m_optimizer.setRepopulator(std::make_shared<ProportionateRepupoluator>());
                break;
            }
        }

        {
            std::shared_ptr<Mutator> mutator = nullptr;
            switch (Config::getInstance().mutatorType) {
            case MUTATOR_RANDOM:
                mutator = std::make_shared<RandomMutator>();
                break;
            default:
            case MUTATOR_THRESHOLD:
                mutator = std::make_shared<ThresholdMutator>();
                break;
            }
            mutator->setMutationRate(static_cast<float>(Config::getInstance().mutationRate));
            m_optimizer.setMutator(mutator);
        }

        {
            std::unique_ptr<LODArchiver> lodArchiver = std::make_unique<LODArchiver>();
            lodArchiver->setFolderName(Config::getInstance().folderName);
            lodArchiver->applyTimestampToFolder(Config::getInstance().timeToFolder);
            lodArchiver->setFileStuffix(Config::getInstance().logSuffix);
            lodArchiver->applyTimestampToFile(Config::getInstance().timeToFile);
            lodArchiver->open();
            m_lod = std::make_shared<LOD>();
            m_lod->setGrid(m_grid);
            m_lod->setArchiver(lodArchiver);

            m_optimizer.setLOD(m_lod);
        }

        {
            //Show timedelta for init
            m_clock_now = HighResClock::now();
            fsec fs = m_clock_now - m_clock_last;
            m_clock_last = m_clock_now;
            ms timeDelta = std::chrono::duration_cast<ms>(fs);
            std::cout << "took " << timeDelta.count() << " ms" << std::endl;
        }

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
        for (int i = 0; i < groups.size(); i++) {
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
        if (Config::getInstance().archiveData) {
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
        getchar();
        //  m_archiver.close();
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