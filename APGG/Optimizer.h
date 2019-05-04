#pragma once
#include <memory>
#include "Grid.h"
#include "Selector.h"
#include "Repopulator.h"
#include "EliteSelector.h"
#include "RandomRepopulator.h"

class Optimizer
{
protected:
    std::shared_ptr<Grid> m_grid;
    std::shared_ptr<Selector> m_selector;
    std::shared_ptr<Repopulator> m_repopulator;

public:
    Optimizer();
    void setGrid(const std::shared_ptr<Grid>& grid);
    void setSelector(const std::shared_ptr<Selector>& selector);
    void setRepopulator(const std::shared_ptr<Repopulator>& repopulator);
    void optmize();
};

