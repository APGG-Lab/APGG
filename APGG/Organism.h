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
    enum Faction { FACTION_COOPERATOR = 0, FACTION_DEFECTOR, FACTION_MORALIST, FACTION_IMMORALIST };
	enum Status { STATUS_ORIGINAL, STATUS_CLONE, STATUS_OFFSPRING, STATUS_DELETED };
	enum ParentStatus { PARENT_ORIGINAL, PARENT_MODIFIED };

	class Organism;
	typedef std::shared_ptr<Organism> pOrganism;
	typedef std::reference_wrapper<Organism> rOrganism;

    class Organism : public std::enable_shared_from_this<Organism>
    {
    public:
        std::array<Genome, nrGenomes> m_genomes;
		std::list<pOrganism> m_children;
		pOrganism m_parent = nullptr;
		std::string m_history = "";


		~Organism() { 
			if (m_status == STATUS_ORIGINAL) {
                std::cout << "Organism delete " 
                 << "original Gen" << m_generation << " ID: " << ID << " Parent: " << getParentID() << " Children: " << getChildIDs() << std::endl;
			}
            else if(m_status == STATUS_DELETED) {
              //  std::cout << "Organism delete "
              //      << "STATUS DELETED Gen" << m_generation << " ID: " << ID << " Parent: " << getParentID() << " Children: " << getChildIDs() << std::endl;
            }
			else {
              //  std::cout << "Organism delete "
              //      << "copy Gen" << m_generation << " ID: " << ID << " Parent: " << getParentID() << " Children: " << getChildIDs() << std::endl;
            }
		}


        unsigned int ID;
        bool m_cooperated;

        bool m_moralist;
        Faction m_faction;
		unsigned int m_generation;

        //@todo startvalue?
        float m_payoff = 1;
		int m_status = STATUS_ORIGINAL;
		int ParentStatus = PARENT_ORIGINAL;

        bool assignProfession(const float cooperationValue);
        bool assignMorals(const float moralValue);
        Faction assignFaction();
        Faction getFaction();
        float getNormalizedPayoff(const float min, const float max);

        void setPayoff(const float payoff);
		void copyTo(pOrganism& copyOrganism);
        pOrganism getPtr() { return shared_from_this(); };
        void clearChilds() {
            if(m_status > 2){
                int test = 0;
            }
            if (m_status < 2) {
                int test = 0;
            }
            m_children.clear();
        }
        void removeChild(const pOrganism& organism) { 
            if (m_status > 2) {
                int test = 0;
            }
            m_children.remove(organism);
        }
        void addChild(const pOrganism& organism) {
            if (m_status > 2) {
                int test = 0;
            }
            for (const auto& child : m_children) {
                if (child.get() == organism.get()) {
                    int test = 0;
                    return;
                }
            }
            m_children.push_back(organism);
        }
        std::string getParentID() {
           // if (m_parent.get() == nullptr) { return "-1"; }
         //   else { return std::to_string(m_parent->ID); }
            return "";
        }
        std::string getChildIDs() {
          /*  if (m_children.empty()) { return "(-1)"; }
            else {
                std::string ret = "(";
                for (auto& child : m_children) {
                    ret += std::to_string(child->ID) + ",";
                }
                ret += ")";
                return ret;
            }*/
            return "";
        }

        std::string getDebugString();
		static void removeAndCleanupChildLists(pOrganism& organism);
    };



}