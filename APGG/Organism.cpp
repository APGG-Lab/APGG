#include "Organism.h"

namespace APGG {
#ifdef DEBUG_EXTREME
    Organism::~Organism()
    {
        if (m_status == STATUS_ORIGINAL) {
            DEBUG_MSG("Organism Destructor original: " + getDebugString());
        }
        else if (m_status == STATUS_DELETED) {
            DEBUG_MSG("Organism Destructor deleted: " + getDebugString());
        }
        else {
            DEBUG_MSG("Organism Destructor Copy: " + getDebugString());
        }
    }
#endif // DEBUG_EXTREME

    bool Organism::assignProfession(const float cooperationValue)
    {
        m_cooperated = m_genomes[GENOME_COOPERATION].getValue() >= cooperationValue;
        return m_cooperated;
    }

    bool Organism::assignMorals(const float moralValue)
    {
        m_moralist = m_genomes[GENOME_MORALS].getValue() >= moralValue;
        return m_moralist;
    }

    Faction Organism::assignFaction()
    {
        assignProfession(getRandomFloat());
        assignMorals(getRandomFloat());

        if (m_cooperated && !m_moralist) m_faction = FACTION_COOPERATOR;
        else if (m_cooperated && m_moralist) m_faction = FACTION_MORALIST;
        else if (!m_cooperated && !m_moralist) m_faction = FACTION_DEFECTOR;
        else m_faction = FACTION_IMMORALIST;

        return m_faction;
    }

    Faction Organism::getFaction()
    {
        return m_faction;
    }

    void Organism::setPayoff(const float payoff)
    {
        m_payoff = payoff;

        if (m_payoff < 0) {
            m_payoff = 0;
        }
    }

	void Organism::copyTo(pOrganism& copyOrganism)
	{
		copyOrganism->m_cooperated = m_cooperated;
		copyOrganism->m_faction = m_faction;
		//copyOrganism->m_genomes = m_genomes;
		copyOrganism->m_moralist = m_moralist;
		copyOrganism->m_payoff = m_payoff;
		copyOrganism->m_status = STATUS_CLONE;
		copyOrganism->ID = ID;
		copyOrganism->m_children = m_children;
		copyOrganism->m_parent = m_parent;
		for (int i = 0; i < m_genomes.size(); i++) {
			copyOrganism->m_genomes[i].setValue(m_genomes[i].getValue());
		}
	}

    void Organism::clearChildren()
    {
        m_children.clear();
    }

    void Organism::removeChild(const pOrganism & organism)
    {
        m_children.remove(organism);
    }

    void Organism::addChild(const pOrganism & organism)
    {
#ifdef DEBUG_EXTREME
        for (const auto& child : m_children) {
            if (child.get() == organism.get()) {
                DEBUG_MSG("Organism AddChild: organism already has this child " + getDebugString());
                DEBUG_MSG("Organism AddChild Child: " + organism->getDebugString());
                return;
            }
        }
#endif // DEBUG_EXTREME

        m_children.push_back(organism);
    }


    float Organism::getNormalizedPayoff(const float min, const float max)
    {
        auto payoff = (m_payoff + std::abs(min)) / (max + std::abs(min));
        return payoff;
    }

    std::string Organism::getDebugString()
    {
        std::string debugString = "";
        debugString += "ID: " + std::to_string(ID) + ":" + std::to_string(m_generation) + " ";
        debugString += ("Parent: " + ((m_parent != nullptr) ? (std::to_string(m_parent->ID) + ":" + std::to_string(m_parent->m_generation)) : " -1") + " ");
        debugString += "Children: ";
        if (m_children.empty()) {
            debugString += " (-1)";
        }
        else {
            debugString += "(";
            for (const pOrganism& child : m_children) {
                debugString += std::to_string(child->ID) + ":" + std::to_string(child->m_generation) +  ",";
            }
            debugString += ")";
        }

        return debugString;
    }
}