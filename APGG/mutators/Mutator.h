#pragma once
#include "../Organism.h"
#include "../Configurable.h"
#include "../grids/Grid.h"
#include <unordered_set>

namespace APGG
{
    /**
    * Base class for the mutators. Keeps a mutation rate (how likely an Organism is mutated).
    */
    class Mutator : public Configurable
    {
    protected:
        float m_mutationRate;
    public:
        void setMutationRate(const float rate);
        virtual void mutate(Grid& grid, const std::unordered_set<GridIndex>& selection) = 0;
		virtual void configure(Config& config) = 0;

        static std::unique_ptr<Mutator> Create(Config& config);
    };
}
