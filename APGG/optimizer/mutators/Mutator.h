#pragma once
#include "../../Organism.h"
#include "../../Configurable.h"

namespace APGG
{
    enum class MutatorType : uint8_t { Random = 0, Threshold, Count };

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
