#include "Selector.h"

#include "EliteSelector.h"
#include "RandomSelector.h"

namespace APGG {

    enum class SelectorType : unsigned long { Elite = 0, Random, Count };

    Selector::Selector() : m_eliminationCount(1)
    {
        m_selection.reserve(m_eliminationCount);
    }

    Selector::Selector(const unsigned int count) : m_eliminationCount(count)
    {
        m_selection.reserve(m_eliminationCount);
    }

    void Selector::setEliminationCount(const unsigned int count)
    {
        m_eliminationCount = count;
    }
	std::unique_ptr<Selector> Selector::Create(Config& config)
    {
        SelectorType selectorType = static_cast<SelectorType>(stoul(config.getValue("selectorType", "0")));

        if (selectorType >= SelectorType::Count) {
            std::cerr << std::endl << "[APGG Error] invalid selector type. SelectorType must be < " << static_cast<int>(SelectorType::Count);
            std::cin.get();
            std::quick_exit(1);
        }

        switch (selectorType) {
        case SelectorType::Elite:
            return std::make_unique<EliteSelector>();
        case SelectorType::Random:
            return std::make_unique<RandomSelector>();
        }
    }
}