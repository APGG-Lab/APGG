#include "Organism.h"

namespace APGG {


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


    float Organism::getNormalizedPayoff(const float min, const float max)
    {
        auto payoff = (m_payoff + std::abs(min)) / (max + std::abs(min));
        return payoff;
    }

    void Organism::removeAndCleanupChildLists(pOrganism& organism){
        if (!organism->m_children.empty()) {
#ifdef DEBUG_EXTREME
            std::cout << "Cleanup organism is not dead: " << "Ptr:" << organism.get() << " ID: " << organism->ID << " Parent: " << organism->getParentID() << " Children: " << organism->getChildIDs() << std::endl;
#endif
            return;
        }

        if (organism->m_parent.get() == nullptr) {
#ifdef DEBUG_EXTREME
            std::cout << "Cleanup organism origin reached: " << "Ptr:" << organism.get() << " ID: " << organism->ID << " Parent: " << organism->getParentID() << " Children: " << organism->getChildIDs() << " Gen:" << organism->m_generation << std::endl;
#endif
            return;
        }

        if (organism->m_parent->m_status != STATUS_CLONE) {
#ifdef DEBUG_EXTREME
            std::cout << "Cleanup organism is not a clone: " << "Ptr:" << organism.get() << " ID: " << organism->ID << " Parent: " << organism->getParentID() << " Children: " << organism->getChildIDs() << std::endl;
#endif // DEBUG_EXTREME
            return;
        }

        organism->m_children.clear();
        removeAndCleanupChildLists(organism->m_parent);
        organism->m_parent = nullptr;

#ifdef DEBUG_EXTREME
        std::cout << "Cleanup organism done: " << "Ptr:" << organism.get() << " ID: " << organism->ID << " Parent: " << organism->getParentID() << " Children: " << organism->getChildIDs() << " Gen:" << organism->m_generation << std::endl;
#endif // DEBUG_EXTREME

	}

}