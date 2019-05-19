#include "Optimizer.h"

namespace APGG {


    void Optimizer::setGrid(const std::shared_ptr<Grid>& grid)
    {
        m_grid = grid;
    }

    void Optimizer::setSelector(const std::shared_ptr<Selector> & selector)
    {
        m_selector = selector;
    }

    void Optimizer::setRepopulator(const std::shared_ptr<Repopulator> & repopulator)
    {
        m_repopulator = repopulator;
    }

    void Optimizer::optmize()
    {
        std::vector<rOrganism> selection = m_selector->select(m_grid);

		m_lod->LODebug(selection);

        m_repopulator->repopulate(m_grid, selection);

    }

	void Optimizer::setLOD(const std::shared_ptr<LOD>& lod) {
		m_lod = lod;
	}


    Optimizer::Optimizer()
    {
    }
}