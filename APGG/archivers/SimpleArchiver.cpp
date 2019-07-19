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

    void SimpleArchiver::archive(const int generation, const int nCooperators, const int nDefectors, const int nMoralists, const int nImmoralist)
    {
        m_fileHandle << generation << ";" << nCooperators << ";" << nDefectors << ";" << nMoralists << ";" << nImmoralist << std::endl;
    }

    void SimpleArchiver::archive(const std::string & line)
    {
        m_fileHandle << line << std::endl;
    }
	void SimpleArchiver::configure(Config& config)
	{
		if (!stoi(config.getValue("timeToFile")) && stoi(config.getValue("timeToFolder"))) {
			std::cerr << std::endl << "[APGG Warning] timeToFile disabled. You may overwrite your previous experiments";
			std::cin.get();
		}

		m_folderName = config.getValue("folderName");
		applyTimestampToFolder(stoi(config.getValue("timeToFolder")));
		m_fileSuffix = config.getValue("timeToFile");
		applyTimestampToFile(stoi(config.getValue("timeToFile")));
	}
}