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

    void Optimizer::setMutator(const std::shared_ptr<Mutator>& mutator)
    {
        m_mutator = mutator;
    }

    void Optimizer::optmize()
    {
        std::vector<rOrganism> selection = m_selector->select(m_grid);

		m_lod->LODebug(selection);

        m_repopulator->repopulate(m_grid, selection);

        m_mutator->mutate(selection);

		for (auto organsim : m_grid->data()) {
			organsim.get().m_payoff = 0;
		}
    }

	//TODO: make mutators, repopulators and selectors configurable too
	void Optimizer::configure(Config& config)
	{
		if (stoul(config.getValue("selectorType")) >= nSelectorTypes) {
			std::cerr << std::endl << "[APGG Error] invalid selector type. selectorType must be < " << nSelectorTypes;
			std::cin.get();
			std::quick_exit(1);
		}

		switch (stoul(config.getValue("selectorType"))) {
		case SELECTOR_ELITE:
			m_selector = std::make_shared<EliteSelector>();
			break;
		default:
		case SELECTOR_RANDOM:
			m_selector = std::make_shared<RandomSelector>();
			break;
		}
		m_selector->configure(config);
	
	
		if (stoul(config.getValue("repopulationType")) >= nRepopulatorTypes) {
			std::cerr << std::endl << "[APGG Error] invalid repopulator type. repopulatorType must be < " << nRepopulatorTypes;
			std::cin.get();
			std::quick_exit(1);
		}

		switch (stoul(config.getValue("repopulationType"))) {
		case REPOPULATOR_RANDOM:
			m_repopulator = std::make_shared<RandomRepopulator>();
			break;
		default:
		case REPOPULATOR_PROPORTIONATE:
			m_repopulator = std::make_shared<ProportionateRepupoluator>();
			break;
		}
		m_repopulator->configure(config);
	
		std::shared_ptr<Mutator> mutator = nullptr;
		switch (stoul(config.getValue("mutatorType"))) {
		case MUTATOR_RANDOM:
			mutator = std::make_shared<RandomMutator>();
			break;
		default:
		case MUTATOR_THRESHOLD:
			mutator = std::make_shared<ThresholdMutator>();
			break;
		}
		mutator->configure(config);
		m_mutator = mutator;
	}

	void Optimizer::setLOD(const std::shared_ptr<LOD>& lod) {
		m_lod = lod;
	}


    Optimizer::Optimizer()
    {
    }
}