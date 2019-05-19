#pragma once
#include <memory>

#include "../Grid.h"

#include "selectors/Selector.h"
#include "repopulators/Repopulator.h"
#include "selectors/EliteSelector.h"
#include "repopulators/RandomRepopulator.h"
#include "repopulators/ProportionateRepopulator.h"
#include "selectors/RandomSelector.h"
#include "Mutator.h"

#include "LOD.h"

namespace APGG {

    class Optimizer
    {
    protected:
        std::shared_ptr<Grid> m_grid;
        std::shared_ptr<Selector> m_selector;
        std::shared_ptr<Repopulator> m_repopulator;
        std::shared_ptr<Mutator> m_mutator;
		std::shared_ptr<LOD> m_lod;

    public:
        Optimizer();
        void setGrid(const std::shared_ptr<Grid>& grid);
        void setSelector(const std::shared_ptr<Selector>& selector);
        void setRepopulator(const std::shared_ptr<Repopulator>& repopulator);
        void setMutator(const std::shared_ptr<Mutator>& mutator);
		void setLOD(const std::shared_ptr<LOD>& lod);

        void optmize();
    };

}