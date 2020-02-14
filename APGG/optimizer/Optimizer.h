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
        Grid* m_grid;
        std::shared_ptr<Selector> m_selector = nullptr;
        std::shared_ptr<Repopulator> m_repopulator = nullptr;
        std::shared_ptr<Mutator> m_mutator = nullptr;
		std::shared_ptr<LOD> m_lod;

    public:
        Optimizer();
        void setGrid(Grid* grid);
        void setSelector(const std::shared_ptr<Selector>& selector);
        void setRepopulator(const std::shared_ptr<Repopulator>& repopulator);
        void setMutator(const std::shared_ptr<Mutator>& mutator);
		void setLOD(const std::shared_ptr<LOD>& lod);

        void optmize(Grid& grid);
		void configure(Config& config);
    };

}