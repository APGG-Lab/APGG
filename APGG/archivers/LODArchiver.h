#pragma once
#include "Archiver.h"
#include "../Organism.h"

namespace APGG {
    /**
    * Basic implementation of the Archiver base class that writes the a line of descent into a file that includes
    * a line for every Organism provided. 
    */
    class LODArchiver : public Archiver
    {
    public:
        LODArchiver();
        LODArchiver(const std::string& folderName, const std::string& fileSuffix);
        void archive(Organism* organism);
        void archive(const std::string& line);
		void configure(Config& config);
    };

}