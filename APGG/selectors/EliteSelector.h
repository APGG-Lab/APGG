#pragma once
#include "Selector.h"

namespace APGG {


    class EliteSelector : public Selector
    {
    public:
        std::unordered_set<GridIndex>& select(Grid& grid);
		void configure(Config& config) override;
    };

}