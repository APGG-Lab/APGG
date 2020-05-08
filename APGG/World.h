#pragma once
#include <iostream>
#include <iomanip> //setFill for init output
#include <chrono>
#include <ctime>
#include <sstream>
#include <cstdlib>

#include "grids/Grid.h"
#include "payoffcalculators/PayoffCalculator.h"
#include "mutators/Mutator.h"
#include "selectors/Selector.h"
#include "repopulators/Repopulator.h"

#include "archivers/SimpleArchiver.h"
#include "archivers/LODArchiver.h"
#include "archivers/ConfigArchiver.h"
#include "LOD.h"

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
        unsigned int m_exponent = 10; ///Exponential logging (0-10,10,20,30,100,200,300,1000,2000,3000,....)
//#endif // !__DEBUG

		bool m_archiveData;

        std::array<unsigned int, 4> m_count;

        std::unique_ptr<Grid> m_grid;
        std::unique_ptr<PayOffCalculator> m_payoffCalculator;
        std::unique_ptr<Selector> m_selector;
        std::unique_ptr<Repopulator> m_repopulator;
        std::unique_ptr<Mutator> m_mutator;

        SimpleArchiver m_archiver;
        LODArchiver m_lodArchiver;
        ConfigArchiver m_configArchiver;
        LOD m_lod;
        

    public:
        void Init(Config & config);
        void Tick();
        void Fini();

        void Evolve();
        unsigned int m_generation = 0;
    };

	
}
