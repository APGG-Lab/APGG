#pragma once
#include <array>
#include <memory>
#include <list>
#include <string>
#include <iostream>
#include "Genome.h"

#ifdef DEBUG_EXTREME
#define DEBUG_MSG(str) do { std::cout << "[APGG DEBUG] " << str << "\n"; } while( false )
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

    /**
    * Represents the agents in a simulation. Keeps and provides relation to the children of this agent
    * that have been generated with this as a parent, it�s own parent and information about it�s own
    * genomes as well as methods to simulate a step in the experiment relating to them.
    */
    class Organism
    {
    public:
        Organism() = default;
        std::array<Genome, nrGenomes> m_genomes;

        Organism* m_parent = nullptr;
        std::list<Organism*> m_children;
#ifdef DEBUG_EXTREME
        //Custom destructor for extreme debugging
        ~Organism();
#endif

#ifdef __DEBUG
        unsigned int ID;
        unsigned int m_generation;
#endif //__DEBUG

        //@todo startvalue?
        float m_payoff = 0;
        Status m_status = Status::Original;
        Faction m_faction;

        bool m_cooperator;
        bool m_moralist;

        bool assignProfession(const float cooperationValue);
        bool assignMorals(const float moralValue);
        Faction& assignFaction();
        Faction getFaction();
        float getNormalizedPayoff(const float min, const float max);

        void setPayoff(const float payoff);
		void copyTo(Organism* copyOrganism);

        void clearChildren();
        void removeChild(Organism* organsim);
        void addChild(Organism* organism);
    };
}
