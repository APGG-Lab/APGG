#pragma once
#include <string>
#include "../Config.h"
#include "Archiver.h"

namespace APGG {
    class ConfigArchiver : public Archiver
    {
    public:
		ConfigArchiver();
		ConfigArchiver(const std::string& folderName, const std::string& fileSuffix);
        void archive(Config& config);
        void archive(const std::string& line);
		void configure(Config& config);
    };

}