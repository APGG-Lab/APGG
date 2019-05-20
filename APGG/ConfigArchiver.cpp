#include "ConfigArchiver.h"

namespace APGG {

	ConfigArchiver::ConfigArchiver() : Archiver()
    {
        m_header = "key;value";
		m_fileBaseName = "config";
    }

	ConfigArchiver::ConfigArchiver(const std::string & folderName, const std::string & fileSuffix) : Archiver(folderName, fileSuffix)
    {
		m_header = "key;value";
		m_fileBaseName = "config";
	}

    void ConfigArchiver::archive(const Config& config)
    {
		m_fileHandle
			<< "numGenerations;" << config.numGenerations << std::endl
			<< "eliminationCount;" << config.eliminationCount << std::endl
			<< "groupSize;" << config.groupSize << std::endl
			<< "width;" << config.width << std::endl
			<< "height;" << config.height << std::endl
			<< "cooperateCost;" << config.cooperateCost << std::endl
			<< "synergyFactor;" << config.synergyFactor << std::endl
			<< "punishmentCost;" << config.punishmentCost << std::endl
			<< "punishmentFine;" << config.punishmentFine << std::endl
			<< "matchupType;" << config.matchupType << std::endl
			<< "selectorType;" << config.selectorType << std::endl
			<< "repopulatorType;" << config.repopulatorType << std::endl
			<< "mutationRate;" << config.mutationRate << "%" << std::endl
			<< "showAllGenerations;" << config.showAllGenerations << std::endl
			<< "archiveData;" << config.archiveData << std::endl
			<< "visualize;" << config.visualize << std::endl
			<< "folderName;" << config.folderName << std::endl
			<< "logSuffix;" << config.logSuffix << std::endl
			<< "timeToFile;" << config.timeToFile << std::endl
			<< "timeToFolder;" << config.timeToFolder << std::endl
			<< "consoleOutExponent;" << config.consoleOutExponent;
    }

    void ConfigArchiver::archive(const std::string & line)
    {
        m_fileHandle << line << std::endl;
    }
}