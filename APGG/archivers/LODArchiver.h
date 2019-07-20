#pragma once
#include "Archiver.h"
#include "../Organism.h"

namespace APGG {

    class LODArchiver : public Archiver
    {
    public:
        LODArchiver();
        LODArchiver(const std::string& folderName, const std::string& fileSuffix);
        void archive(const pOrganism& organism);
        void archive(const std::string& line);
		void configure(Config& config);
    };

}