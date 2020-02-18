#pragma once
#include <memory>

#include "../grids/Grid.h"

#include "selectors/Selector.h"
#include "repopulators/Repopulator.h"
//#include "selectors/EliteSelector.h"
#include "repopulators/RandomRepopulator.h"
#include "repopulators/ProportionateRepopulator.h"
#include "selectors/RandomSelector.h"

#include "mutators/Mutator.h"
#include "mutators/RandomMutator.h"
//#include "mutators/ThresholdMutator.h"

#include "LOD.h"

namespace APGG {

    class Optimizer : public Configurable
    {
    protected:
        std::unique_ptr<Selector> m_selector;
        std::unique_ptr<Repopulator>  m_repopulator;
        std::unique_ptr<Mutator>  m_mutator;

    public:
        void optmize(Grid& grid, LOD& lod);
		void configure(Config& config);
    };

}