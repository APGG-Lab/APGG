#include "Selector.h"

namespace APGG {


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
        m_selection.reserve(m_eliminationCount);
    }
}