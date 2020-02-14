#pragma once
#include <vector>
#include "../../Organism.h"
#include "../../grids/Grid.h"
#include <unordered_set>
namespace APGG {

    enum class SelectorType : unsigned long { Elite = 0, Random, Count};

    class Selector : public Configurable
    {
    protected:
        std::vector<rOrganism> m_selection;
        std::vector<unsigned int> m_selection2;
        unsigned int m_eliminationCount;
    public:
        Selector();
        Selector(const unsigned int count);
        void setEliminationCount(const unsigned int count);
        virtual std::unordered_set<unsigned int> select(Grid& grid) = 0;
		virtual void configure(Config& config) = 0;
    };
}