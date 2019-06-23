#pragma once
#include "../../Organism.h"

namespace APGG
{
    constexpr unsigned int nMutatorTypes = 2;
    enum MutatorTypes { MUTATOR_RANDOM, MUTATOR_THRESHOLD };

    class Mutator
    {
    protected:
        float m_motationRate;
    public:
        void setMutationRate(const float rate);
        virtual void mutate(const std::vector<rOrganism>& selection) = 0;
    };
}
