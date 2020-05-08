#pragma once
#include "DefaultGrid.h"
#include "SpatialGrid.h"

namespace APGG {
    enum class GridType : unsigned long { Default = 0, Spatial, Count };

    static std::unique_ptr<Grid> CreateGrid(Config& config)
    {
        GridType gridType = static_cast<GridType>(stoul(config.getValue("gridType", "0")));

        if (gridType >= GridType::Count) {
            std::cerr << std::endl << "[APGG Error] invalid grid type. gridType must be < " << static_cast<int>(GridType::Count);
            std::cin.get();
            std::quick_exit(1);
        }

        std::unique_ptr<Grid> grid;

        switch (gridType) {
        case GridType::Default:
            return std::make_unique<DefaultGrid>();
        default:
        case GridType::Spatial:
            return std::make_unique<SpatialGrid>();
        }
    }
}