#pragma once
#include "../Organism.h"

namespace APGG
{
    class Mutator
    {
    private:
        float m_motationRate;

    public:
        void setMutationRate(const float rate);
        void mutate(const std::vector<rOrganism>& selection);
    };
}
