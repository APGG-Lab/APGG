#pragma once
#include "Selector.h"

namespace APGG {

    class RandomSelector : public Selector
    {
    public:
        RandomSelector();
        RandomSelector(const unsigned int eliminationCount);
        std::vector<rOrganism> select(std::shared_ptr<Grid>& grid);
    };

}