#pragma once
#include <string>
#include "../Config.h"
#include "Archiver.h"

namespace APGG {
    /**
    * Basic implementation of the Archiver base class that writes information about the config used in the current 
    * experiment into a file.
    */
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