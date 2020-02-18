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

    Faction& Organism::assignFaction()
    {
        assignProfession(getRandomFloat());
        assignMorals(getRandomFloat());


        if (m_cooperated && !m_moralist) m_faction = Faction::Cooperator;
        else if (m_cooperated && m_moralist) m_faction = Faction::Moralist;
        else if (!m_cooperated && !m_moralist) m_faction = Faction::Defector;
        else m_faction = Faction::Immoralist;

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

    void Organism::copyTo(Organism* copyOrganism)
    {
        copyOrganism->m_cooperated = m_cooperated;
      //  copyOrganism->m_faction = m_faction;
        //copyOrganism->m_genomes = m_genomes;
        copyOrganism->m_moralist = m_moralist;
        copyOrganism->m_payoff = m_payoff;
        copyOrganism->m_status = Status::Copy;
#ifdef __DEBUG1
        copyOrganism->ID = ID;
        copyOrganism->m_mutated = m_mutated;
        copyOrganism->m_generation = m_generation;
#endif
        copyOrganism->m_parent = m_parent;
        copyOrganism->m_children = m_children;
       // copyOrganism->m_genomes = m_genomes;
        for (size_t i = 0; i < m_genomes.size(); i++) {
            copyOrganism->m_genomes[i].setValue(m_genomes[i].getValue());
        }
    }

    void Organism::clearChildren()
    {
        m_children.clear();
    }

    void Organism::removeChild(Organism* organsim)
    {
        m_children.remove(organsim);
    }

    void Organism::addChild(Organism* organism)
    {
        m_children.push_back(organism);
    }

    float Organism::getNormalizedPayoff(const float min, const float max)
    {
        auto payoff = (m_payoff + std::abs(min)) / (max + std::abs(min));
        return payoff;
    }
}
