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
    enum GenomeNames { GENOME_COOPERATION = 0, GENOME_MORALS, GENOME_EXTRA1, GENOME_EXTRA2, GENOME_EXTRA3 };
    enum Faction : uint8_t { Cooperator = 0, Defector, Moralist, Immoralist, Count };
	enum class Status : bool { Original = false, Copy = true };
	enum ParentStatus { PARENT_ORIGINAL, PARENT_MODIFIED };

	class Organism;
	typedef std::shared_ptr<Organism> pOrganism;
	typedef std::reference_wrapper<Organism> rOrganism;

    class Organism
    {
    public:
        Organism(const uint8_t numberOfGenomes);
        std::vector<Genome> m_genomes;

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

        bool m_cooperated;
        bool m_moralist;

        //@todo startvalue?
        float m_payoff = 0;
        Status m_status = Status::Original;
        Faction m_faction;

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
