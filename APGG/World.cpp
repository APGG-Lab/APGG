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
              << "\tC(%): " << m_count[FACTION_COOPERATOR] << "(" << m_count[FACTION_COOPERATOR] /size*100 << ")"
              << "\tD(%): " << m_count[FACTION_DEFECTOR] << "(" << m_count[FACTION_DEFECTOR] /size * 100 << ")"
              << "\tM(%): " << m_count[FACTION_MORALIST] << "(" << m_count[FACTION_MORALIST] /size * 100 << ")"
              << "\tI(%): " << m_count[FACTION_IMMORALIST] << "(" << m_count[FACTION_IMMORALIST] /size * 100 << ")"
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
    int localCooperation = 0;
    float localPayoff = 0;
    m_matchupGenerator.generateGroups();

    std::vector<Group> groups = m_matchupGenerator.getGroups();
    std::array<unsigned int, 4> factionCount;

    //@todo for(group:groups) could be better. 
    for (int i = 0; i < groups.size(); i++) {
        localCooperation = 0;
        std::fill(std::begin(factionCount), std::end(factionCount), 0);

        for (pOrganism& organism : groups[i].data()) {
            Faction faction = organism->assignFaction();
            m_count[faction]++;
            factionCount[faction]++;
        }


        //Precalculate costs, fines and payoffs
        float punishmentCost = (factionCount[FACTION_DEFECTOR] + factionCount[FACTION_MORALIST])
                                    * static_cast<float>(Config::getInstance().punishmentCost);

        float punishmentFine = (factionCount[FACTION_MORALIST] + factionCount[FACTION_IMMORALIST])
            * static_cast<float>(Config::getInstance().punishmentFine);

        localPayoff = Config::getInstance().synergyFactor *
            static_cast<float>(factionCount[FACTION_COOPERATOR] + factionCount[FACTION_MORALIST]) / (groups[i].size());

        //Apply costs, fines and payoffs to organisms
        for (pOrganism& organism : groups[i].data()) {
            organism->m_payoff += localPayoff;

            if (organism->m_moralist) { //Subtract punishment costs from moralists/immoralists
                organism->m_payoff -= punishmentCost;
            };

            if (!organism->m_cooperated) {//Substract punishment fine from defectors/immoralists
                organism->m_payoff -= punishmentFine;
            }
            else {
                organism->m_payoff -= 1; //Substract 1 from cooperators / moralists
            }
        }
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

    m_archiver.close();
}

void World::Evolve()
{
	m_grid->sortByFitness();
	for (unsigned int i = m_grid->size() - 1; i > m_grid->size() - 1 - Config::getInstance().eliminationCount; i--) {
        //Reset organism
		m_grid->getOrganism(i)->m_genomes[0].shuffle();
        m_grid->getOrganism(i)->m_genomes[1].shuffle();
        m_grid->getOrganism(i)->m_payoff = 1.0f;
	}
	m_generation++;
}
