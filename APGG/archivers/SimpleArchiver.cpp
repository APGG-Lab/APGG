#include "SimpleArchiver.h"

namespace APGG {

    SimpleArchiver::SimpleArchiver() : Archiver()
    {
        m_header = "generation;nCooperators;nDefectors;nMoralists;nImmoralists";
    }

    SimpleArchiver::SimpleArchiver(const std::string & folderName, const std::string & fileSuffix) : Archiver(folderName, fileSuffix)
    {
        m_header = "generation;nCooperators;nDefectors;nMoralists;nImmoralists";
    }

    void SimpleArchiver::archive(const int generation, const std::array<unsigned int, Faction::Count>& counter)
    {
        m_fileHandle << generation << ";" 
            << counter[Faction::Cooperator] << ";" 
            << counter[Faction::Defector] << ";"
            << counter[Faction::Moralist] << ";" 
            << counter[Faction::Immoralist] << "\n";
    }

    void SimpleArchiver::archive(const std::string & line)
    {
        m_fileHandle << line << "\n";
    }
	void SimpleArchiver::configure(Config& config)
	{
		if (!stoi(config.getValue("timeToFile")) && stoi(config.getValue("timeToFolder"))) {
			std::cerr << "\n[APGG Warning] timeToFile disabled. You may overwrite your previous experiments";
			std::cin.get();
		}

		m_folderName = config.getValue("folderName");
		applyTimestampToFolder(stoi(config.getValue("timeToFolder")));
		m_fileSuffix = config.getValue("logSuffix");
		applyTimestampToFile(stoi(config.getValue("timeToFile")));
	}
}