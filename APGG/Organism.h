#pragma once
#include <array>
#include <memory>
#include <list>
#include <string>
#include <iostream>
#include "Genome.h"

#ifdef DEBUG_EXTREME
#define DEBUG_MSG(str) do { std::cout << "[APGG DEBUG] " << str << std::endl; } while( false )
#else
#define DEBUG_MSG(str) do { } while ( false )
#endif
//info about do while: https://stackoverflow.com/questions/3371540/c-enable-disable-debug-messages-of-stdcouts-on-the-fly#comment11259287_3371577


namespace APGG {

    constexpr unsigned int nrGenomes = 2;

    enum GenomeNames { GENOME_COOPERATION = 0, GENOME_MORALS, GENOME_HISTORY1, GENOME_HISTORY2, GENOME_HISTORY3 };
    enum Faction : uint8_t { Cooperator = 0, Defector, Moralist, Immoralist, Count };
	enum class Status : bool { Original = false, Copy = true };
	enum ParentStatus { PARENT_ORIGINAL, PARENT_MODIFIED };

	class Organism;
	typedef std::shared_ptr<Organism> pOrganism;
	typedef std::reference_wrapper<Organism> rOrganism;

    class Organism
    {
    public:
        std::array<Genome, nrGenomes> m_genomes;

        Organism* m_parent2 = nullptr;
        std::list<Organism*> m_children2;
#ifdef DEBUG_EXTREME
        //Custom destructor for extreme debugging
        ~Organism();
#endif

#ifdef __DEBUG1
        unsigned int ID;
        unsigned int m_generation;
#endif __DEBUG 1

        bool m_cooperated;
        bool m_moralist;

        //@todo startvalue?
        float m_payoff = 0;
        Status m_status = Status::Original;

        bool assignProfession(const float cooperationValue);
        bool assignMorals(const float moralValue);
        Faction assignFaction();
        Faction getFaction();
        float getNormalizedPayoff(const float min, const float max);

        void setPayoff(const float payoff);
		void copyTo(pOrganism& copyOrganism);
		void copyTo2(Organism* copyOrganism);
       // pOrganism getPtr() { return shared_from_this(); };


        void clearChildren();
        void removeChild(const pOrganism& organism);
        void addChild(const pOrganism& organism);

        void clearChildren2();
        void removeChild2(Organism* organsim);
        void addChild2(Organism* organism);

        std::string getDebugString();
    };



}