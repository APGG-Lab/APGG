#include "Optimizer.h"

namespace APGG {


    void Optimizer::setGrid(Grid* grid)
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

    void Optimizer::optmize(Grid& grid)
    {
		std::unordered_set<unsigned int> selection = m_selector->select(grid);
       // std::vector<rOrganism> selection = m_selector->select(m_grid);

		//m_lod->LODebug(selection);

        m_repopulator->repopulate(grid, selection);

       // m_mutator->mutate(selection);

		//for (auto organsim : m_grid->data()) {
	//		organsim.get().m_payoff = 0;
	//	}
    }

	//TODO: make mutators, repopulators and selectors configurable too
	void Optimizer::configure(Config& config)
	{
		SelectorType selectorType = static_cast<SelectorType>(stoul(config.getValue("selectorType")));
		RepopulatorType repopulatorType = static_cast<RepopulatorType>(stoul(config.getValue("repopulationType")));
		MutatorType mutatorType = static_cast<MutatorType>(stoul(config.getValue("mutatorType")));

		if (selectorType >= SelectorType::Count) {
			std::cerr << std::endl << "[APGG Error] invalid selector type. selectorType must be < " << static_cast<int>(SelectorType::Count);
			std::cin.get();
			std::quick_exit(1);
		}

		if (repopulatorType >= RepopulatorType::Count) {
			std::cerr << std::endl << "[APGG Error] invalid repopulator type. repopulatorType must be < " << static_cast<int>(RepopulatorType::Count);
			std::cin.get();
			std::quick_exit(1);
		}

		if (mutatorType >= MutatorType::Count) {
			std::cerr << std::endl << "[APGG Error] invalid mutator type. mutatorType must be < " << static_cast<int>(MutatorType::Count);
			std::cin.get();
			std::quick_exit(1);
		}

		switch (selectorType) {
		case SelectorType::Elite:
			//m_selector = std::make_shared<EliteSelector>();
			break;
		default:
		case SelectorType::Random:
			m_selector = std::make_shared<RandomSelector>();
			break;
		}
		m_selector->configure(config);
	
	
		switch (repopulatorType) {
		case RepopulatorType::Random:
		//	m_repopulator = std::make_shared<RandomRepopulator>();
			break;
		default:
		case RepopulatorType::Proportionate:
			m_repopulator = std::make_shared<ProportionateRepupoluator>();
			break;
		}
		m_repopulator->configure(config);
	

	//	std::shared_ptr<Mutator> mutator = nullptr;
		switch (mutatorType) {
		case MutatorType::Random:
			//mutator = std::make_shared<RandomMutator>();
			break;
		default:
		case MutatorType::Threshold:
		//	mutator = std::make_shared<ThresholdMutator>();
			break;
		}
	//	mutator->configure(config);
	//	m_mutator = mutator;
	}

	void Optimizer::setLOD(const std::shared_ptr<LOD>& lod) {
		m_lod = lod;
	}


    Optimizer::Optimizer()
    {
    }
}