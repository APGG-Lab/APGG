#pragma once
#include "../../Organism.h"
#include "../../Configurable.h"

namespace APGG
{
    constexpr unsigned int nMutatorTypes = 2;
    enum MutatorTypes { MUTATOR_RANDOM, MUTATOR_THRESHOLD };

    class Mutator : public Configurable
    {
    protected:
        float m_mutationRate;
    public:
        void setMutationRate(const float rate);
        virtual void mutate(const std::vector<rOrganism>& selection) = 0;
		virtual void configure(Config& config) = 0;
    };
}
