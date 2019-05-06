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
        std::fill(std::begin(m_count), std::end(m_count), 0);

        m_grid = std::make_shared<Grid>();
        m_grid->rebuildCache();

        if (m_grid->size() % Config::getInstance().groupSize != 0) {
            std::cerr << std::endl << "[APGG Error] invalid group size. Gridsize (height*width) % Groupsize must be 0";
            std::cin.get();
            std::quick_exit(1);
        }

        m_matchupGenerator.setGroupSize(Config::getInstance().groupSize);
        m_matchupGenerator.setGrid(m_grid);


        m_archiver.setFolderName(Config::getInstance().folderName);
        m_archiver.applyTimestampToFolder(false);
        m_archiver.setFileStuffix(Config::getInstance().logSuffix);
        m_archiver.applyTimestampToFile(true);
        m_archiver.open();

        m_payoffCalculator.setCooperationCost(1.0f);
        m_payoffCalculator.setSynergyFactor(static_cast<float>(Config::getInstance().synergyFactor));
        m_payoffCalculator.setPunishmentBaseCost(static_cast<float>(Config::getInstance().punishmentCost));
        m_payoffCalculator.setPunishmentBaseFine(static_cast<float>(Config::getInstance().punishmentFine));

        m_optimizer.setGrid(m_grid);
        m_optimizer.setSelector(std::make_shared<RandomSelector>(Config::getInstance().eliminationCount));
        m_optimizer.setRepopulator(std::make_shared<ProportionateRepupoluator>());

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
        fsec fs = m_clock_now - m_clock_start;
        ms timeDelta = std::chrono::duration_cast<ms>(fs);
        std::cout << "[APGG] Fini (took " << timeDelta.count() << " ms)" << std::endl;

        //  m_archiver.close();
    }

    void World::Evolve()
    {
        m_optimizer.optmize();
        m_grid->rebuildCache();
        m_generation++;
    }

}