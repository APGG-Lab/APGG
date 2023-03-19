#pragma once
#include <string>
#include "../Organism.h"
#include "Archiver.h"

namespace APGG {
    /**
    * Basic implementation of the Archiver base class that writes the current faction count of a generation to a file.
    */
    class SimpleArchiver : public Archiver
    {
    public:
        SimpleArchiver();
        SimpleArchiver(const std::string& folderName, const std::string& fileSuffix);
        void archive(const int generation, const std::array<unsigned int, Faction::Count>& counter);
        void archive(const std::string& line);
		void configure(Config& config);
    };

}