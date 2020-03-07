#pragma once
#include <iostream>
#include <iomanip> //setFill for init output
#include <chrono>
#include <ctime>
#include <sstream>
#include <cstdlib>
#include "grids/DefaultGrid.h"
#include "grids/SpatialGrid.h"
#include "payoffcalculators/DefaultPayoffCalculator.h"
#include "archivers/SimpleArchiver.h"
#include "archivers/LODArchiver.h"
#include "archivers/ConfigArchiver.h"
#include "optimizer/Optimizer.h"

typedef std::chrono::steady_clock HighResClock;
typedef std::chrono::milliseconds ms;
typedef std::chrono::duration<double> fsec;


#include <fstream>

namespace APGG {


    class World
    {
    private:
        std::chrono::time_point<std::chrono::steady_clock> m_clock_start;
        std::chrono::time_point<std::chrono::steady_clock> m_clock_now;
        std::chrono::time_point<std::chrono::steady_clock> m_clock_last;
        void printStatus();
        void printInitMessage();

//#ifdef __DEBUG
        int m_exponent = 10; ///Exponential logging (0-10,10,20,30,100,200,300,1000,2000,3000,....)
//#endif // !__DEBUG


		bool m_archiveData;

        std::array<unsigned int, 4> m_count;

        //DefaultMatchupGenerator m_matchupGenerator;
        DefaultPayOffCalculator m_payoffCalculator;
        SimpleArchiver m_archiver;
        LODArchiver m_lodArchiver;
        ConfigArchiver m_configArchiver;
        Optimizer m_optimizer;
        LOD m_lod;
        SpatialGrid m_grid;

    public:
        void Init(Config & config);
        void Tick();
        void Fini();

        void Evolve();
        unsigned int m_generation = 0;
    };

	
}
