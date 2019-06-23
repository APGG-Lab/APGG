#pragma once
#include "Mutator.h"
namespace APGG {
    class RandomMutator : public Mutator
    {
    public:
        void mutate(const std::vector<rOrganism>& selection);
    };
}


