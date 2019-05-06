#include "Config.h"

namespace APGG {

    Config::Config()
    {

    }

    Config& Config::getInstance()
    {
        static Config instance;
        return instance;
    }

}