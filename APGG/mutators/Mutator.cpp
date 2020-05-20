#include "Mutator.h"

#include "RandomMutator.h"
#include "ThresholdMutator.h"

namespace APGG
{
	enum class MutatorType : uint8_t { Random = 0, Threshold, Count };

	void Mutator::setMutationRate(const float rate)
	{
		m_mutationRate = rate;
	}

	std::unique_ptr<Mutator> Mutator::Create(Config& config)
    {
        MutatorType selectorType = static_cast<MutatorType>(stoul(config.getValue("mutatorType", "0")));

        if (selectorType >= MutatorType::Count) {
            std::cerr << std::endl << "[APGG Error] invalid mutator type. MutatorType must be < " << static_cast<int>(MutatorType::Count);
            std::cin.get();
            std::quick_exit(1);
        }

        switch (selectorType) {
        case MutatorType::Random:
            return std::make_unique<RandomMutator>();
        case MutatorType::Threshold:
            return std::make_unique<ThresholdMutator>();
        }
    }
}