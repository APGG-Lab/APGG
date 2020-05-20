#include "Repopulator.h"

#include "RandomRepopulator.h"
#include "ProportionateRepopulator.h"
#include "SpatialRepopulator.h"

namespace APGG
{
	enum class RepopulatorType : uint8_t { Random = 0, Proportionate, Spatial, Count };

	std::unique_ptr<Repopulator> Repopulator::Create(Config& config)
    {
        RepopulatorType selectorType = static_cast<RepopulatorType>(stoul(config.getValue("repopulationType", "0")));

        if (selectorType >= RepopulatorType::Count) {
            std::cerr << std::endl << "[APGG Error] invalid repopulator type. RepopulatorType must be < " << static_cast<int>(RepopulatorType::Count);
            std::cin.get();
            std::quick_exit(1);
        }

        switch (selectorType) {
        case RepopulatorType::Random:
            return std::make_unique<RandomRepopulator>();
        case RepopulatorType::Proportionate:
            return std::make_unique<ProportionateRepupoluator>();
        case RepopulatorType::Spatial:
            return std::make_unique<SpatialRepopulator>();
        }
    }
}