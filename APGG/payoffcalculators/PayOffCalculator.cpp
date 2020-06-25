#include "PayoffCalculator.h"

#include "DefaultPayoffCalculator.h"
#include "GroupLevelPayoffCalculator.h"
namespace APGG {

    enum class PayoffCalculatorType : unsigned long { Default = 0, Group, Count };

    PayoffCalculator::PayoffCalculator() : m_synergyFactor(1), m_punishmentCostBase(1.0f), m_punishmentFineBase(1.0f), m_allowPayoffBelowZero(false)
    {
    }

    void PayoffCalculator::setSynergyFactor(const float factor)
    {
        m_synergyFactor = factor;
    }

    void PayoffCalculator::setPunishmentBaseCost(const float cost)
    {
        m_punishmentCostBase = cost;
    }

    void PayoffCalculator::setPunishmentBaseFine(const float fine)
    {
        m_punishmentFineBase = fine;
    }

    void PayoffCalculator::setCooperationCost(const float cost)
    {
        m_cooperationCost = cost;
    }

    void PayoffCalculator::allowPayoffBelowZero(const bool status)
    {
        m_allowPayoffBelowZero = status;
    }

	std::unique_ptr<PayoffCalculator> PayoffCalculator::Create(Config& config)
	{
        PayoffCalculatorType payOffCalculatorType = static_cast<PayoffCalculatorType>(stoul(config.getValue("payoffType", "0")));

        if (payOffCalculatorType >= PayoffCalculatorType::Count) {
            std::cerr << std::endl << "[APGG Error] invalid payoffcalculator type. PayoffCalculatorType must be < " << static_cast<int>(PayoffCalculatorType::Count);
            std::cin.get();
            std::quick_exit(1);
        }

        switch (payOffCalculatorType) {
        case PayoffCalculatorType::Default:
            return std::make_unique<DefaultPayoffCalculator>();
        case PayoffCalculatorType::Group:
            return std::make_unique<GroupLevelPayoffCalculator>();
        default:
            std::cerr << std::endl << "[APGG Error] Payoffcalculator isn't defined in PayoffCalculator::Create switch case statement" << std::endl;
            std::cin.get();
            std::quick_exit(1);
        }
	}
}