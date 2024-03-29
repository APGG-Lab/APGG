#pragma once
#include <vector>
#include "../Organism.h"
#include "../grids/Grid.h"
#include <unordered_set>
namespace APGG 
{
    /**
    * Base class for the selectors. Keeps informaton about a selection and how many agents should be eliminated.
    */
    class Selector : public Configurable
    {
    protected:
        std::unordered_set<GridIndex> m_selection;
        unsigned int m_eliminationCount;
    public:
        Selector();
        Selector(const unsigned int count);
        void setEliminationCount(const unsigned int count);
        virtual std::unordered_set<GridIndex>& select(Grid& grid) = 0;
		virtual void configure(Config& config) = 0;

        static std::unique_ptr<Selector> Create(Config& config);
    };
}