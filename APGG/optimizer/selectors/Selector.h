#pragma once
#include <vector>
#include "../../Organism.h"
#include "../../Grid.h"
class Selector
{
protected:
    std::vector<pOrganism> m_selection;
    unsigned int m_eliminationCount;
public:
    Selector();
    Selector(const unsigned int count);
    void setEliminationCount(const unsigned int count);
    virtual std::vector<pOrganism> select(std::shared_ptr<Grid>& grid) = 0;
};