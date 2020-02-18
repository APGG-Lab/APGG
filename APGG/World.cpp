#include "World.h"


namespace APGG {

    void World::printStatus()
    {
//#ifdef __DEGBUG


        if (m_generation %m_exponent != 0) {
            return;
        }

        m_clock_now = HighResClock::now();
        fsec fs = m_clock_now - m_clock_last;
        m_clock_last = m_clock_now;
        ms timeDelta = std::chrono::duration_cast<ms>(fs);
      //  float size = static_cast<float>(m_grid->getWidth()) * m_grid->getHeight();

        std::cout << "Generation:" << m_generation
         //   << "\tC(%): " << m_count[FACTION_COOPERATOR] << "(" << m_count[FACTION_COOPERATOR] / size * 100 << ")"
        //    << "\tD(%): " << m_count[FACTION_DEFECTOR] << "(" << m_count[FACTION_DEFECTOR] / size * 100 << ")"
         //   << "\tM(%): " << m_count[FACTION_MORALIST] << "(" << m_count[FACTION_MORALIST] / size * 100 << ")"
        //    << "\tI(%): " << m_count[FACTION_IMMORALIST] << "(" << m_count[FACTION_IMMORALIST] / size * 100 << ")"
            << "\ttook: " << timeDelta.count() << " ms" << std::endl;

        if (m_generation >= m_exponent * 10) {
            //Only increase the exponent, when m_generation reaches m_exponent
            //otherwise we'll print only at 1,10,100,1000,...

            m_exponent *= 10;
        }
//#endif // !__DEGBUG

    }

    void World::Init(Config& config)
    {
        m_clock_start = m_clock_now = m_clock_last = HighResClock::now();
        std::fill(std::begin(m_count), std::end(m_count), 0);

        int val = sizeof(Organism);
        int val2 = sizeof(Status);
        //Setup the grid
        m_grid = Grid();
        m_grid.configure(config);

        //Setup the matchup/group generator
        m_matchupGenerator.setGrid(&m_grid);
        m_matchupGenerator.configure(config);

        //Setup the payoff calculator
        m_payoffCalculator.configure(config);

      //  m_optimizer.setGrid(&m_grid);
        m_optimizer.configure(config);

       	m_archiver.configure(config);
        m_archiver.open();

        std::unique_ptr<LODArchiver> lodArchiver = std::make_unique<LODArchiver>();
        lodArchiver->configure(config);

  //      {

  //      }

        {
        }

  
  //      {


  //          lodArchiver->open();
            m_lod = std::make_shared<LOD>();
            m_lod->setArchiver(lodArchiver);
  //          m_lod->setGrid(m_grid);
  //          m_lod->setArchiver(lodArchiver);

            m_optimizer.setLOD(m_lod);
  //      }

		//{
		//	ConfigArchiver configarchiver = ConfigArchiver();
		//	configarchiver.configure(config);
		//	configarchiver.open();
		//	configarchiver.archive(config);
		//	configarchiver.close();
		//}

        {
            //Show timedelta for init
            m_clock_now = HighResClock::now();
            fsec fs = m_clock_now - m_clock_last;
            m_clock_last = m_clock_now;
            ms timeDelta = std::chrono::duration_cast<ms>(fs);

            std::stringstream ss;
               ss <<
                "[APGG] Init Experiment #" << std::setfill('0') << std::setw(5) << config.getID()
                << "\t(Group " << config.getValue("folderName")
                << " Exp:" << config.getValue("logSuffix")
                << " Syn" << config.getValue("synergyFactor")
                << ") [took " << timeDelta.count() << " ms]" << std::endl;

            std::cout << ss.str() ;
        }

		//m_archiveData = stoi(config.getValue("archiveData"));

    }

    void World::Tick()
    {
        m_matchupGenerator.generateGroups();

        std::vector<Group>& groups = m_matchupGenerator.getGroups();

        

        for (Group& group : groups) {
            for (const unsigned int& index : group.data()) {
                Faction& faction = m_grid[index].assignFaction();
                group.increaseFactionCount(faction);
            }

            m_payoffCalculator.setCounters(group.getFactionCounter());
            m_payoffCalculator.calculateCosts(group.size());
            m_payoffCalculator.applyPayoff(m_grid, group);
        }

        m_archiver.archive(m_generation, m_grid.getFactionCount());


//#ifdef __DEBUG
//        //Only draw slow debug messages when in DEBUG mode
  //      printStatus();
//#endif // __DEBUG

    }

    void World::Fini()
    {

     //   m_grid.sortByFitness();
       // m_lod->logIterative2(&m_grid.getTopOrganism());
        m_lod->logTop(m_grid);
        for (Organism& organism : m_grid.getData()) {
            m_lod->wipe(organism);
        }

        m_grid.wipe();
    //    m_lod->wipe();
     //   m_grid.wipe();

        std::cout << "Fini";
     /*   m_lod->logTop();

        m_grid->wipe();

        fsec fs = m_clock_now - m_clock_start;
        ms timeDelta = std::chrono::duration_cast<ms>(fs);
        std::cout << "[APGG] Fini (took " << timeDelta.count() << " ms)" << std::endl;
        ;*/
        m_archiver.close();
    }

    void World::Evolve()
    {
        m_optimizer.optmize(m_grid);
        m_grid.setGeneration(m_generation++);

      /*  m_grid->rebuildCache();

		;*/
    }

	void World::printLOD(const pOrganism& organism)
	{
		
	}

}
