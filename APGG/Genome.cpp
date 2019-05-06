#include "Genome.h"

namespace APGG {


    Genome::Genome() : m_value(getRandomFloat())
    {
    }

    float Genome::getValue() const
    {
        return m_value;
    }

    void Genome::setValue(const float value)
    {
        m_value = value;
    }

    void Genome::shuffle()
    {
        m_value = getRandomFloat();
    }

}