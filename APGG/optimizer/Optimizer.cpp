#include "Optimizer.h"

namespace APGG {


    void Optimizer::optmize(Grid& grid, LOD& lod)
    {
		std::unordered_set<unsigned int>& selection = m_selector->select(grid);

		lod.LOD2(grid, selection);

        m_repopulator->repopulate(grid, selection);

        m_mutator->mutate(grid, selection);
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
			m_selector = std::make_unique<RandomSelector>();
			break;
		}
		m_selector->configure(config);
	
	
		switch (repopulatorType) {
		case RepopulatorType::Random:
		//	m_repopulator = std::make_shared<RandomRepopulator>();
			break;
		default:
		case RepopulatorType::Proportionate:
			m_repopulator = std::make_unique<ProportionateRepupoluator>();
			break;
		}
		m_repopulator->configure(config);
	

		switch (mutatorType) {
		case MutatorType::Random:
			m_mutator = std::make_unique<RandomMutator>();
			break;
		default:
		case MutatorType::Threshold:
			m_mutator = std::make_unique<RandomMutator>();

		//	m_mutator = std::make_shared<ThresholdMutator>();
			break;
		}
		m_mutator->configure(config);
	}
}