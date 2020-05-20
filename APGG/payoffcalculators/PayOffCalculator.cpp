#include "PayOffCalculator.h"

#include "DefaultPayoffCalculator.h"

namespace APGG {

    enum class PayOffCalculatorType : unsigned long { Default = 0, Count };

    PayOffCalculator::PayOffCalculator() : m_synergyFactor(1), m_punishmentCostBase(1.0f), m_punishmentFineBase(1.0f), m_allowPayoffBelowZero(false)
    {
    }

    void PayOffCalculator::setSynergyFactor(const float factor)
    {
        m_synergyFactor = factor;
    }

    void PayOffCalculator::setPunishmentBaseCost(const float cost)
    {
        m_punishmentCostBase = cost;
    }

    void PayOffCalculator::setPunishmentBaseFine(const float fine)
    {
        m_punishmentFineBase = fine;
    }

    void PayOffCalculator::setCooperationCost(const float cost)
    {
        m_cooperationCost = cost;
    }

    void PayOffCalculator::allowPayoffBelowZero(const bool status)
    {
        m_allowPayoffBelowZero = status;
    }

	std::unique_ptr<PayOffCalculator> PayOffCalculator::Create(Config& config)
	{
        PayOffCalculatorType payOffCalculatorType = static_cast<PayOffCalculatorType>(stoul(config.getValue("payoffType", "0")));

        if (payOffCalculatorType >= PayOffCalculatorType::Count) {
            std::cerr << std::endl << "[APGG Error] invalid grid type. PayOffCalculatorType must be < " << static_cast<int>(PayOffCalculatorType::Count);
            std::cin.get();
            std::quick_exit(1);
        }

        switch (payOffCalculatorType) {
        case PayOffCalculatorType::Default:
            return std::make_unique<DefaultPayOffCalculator>();
        }
	}
}