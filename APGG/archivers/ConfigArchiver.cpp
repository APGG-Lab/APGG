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

    void ConfigArchiver::archive(Config& config)
    {
		m_fileHandle
			<< "numGenerations;" << config.getValue("numGenerations") << std::endl
			<< "eliminationCount;" << config.getValue("eliminationCount") << std::endl
			<< "groupSize;" << config.getValue("groupSize") << std::endl
			<< "width;" << config.getValue("width") << std::endl
			<< "height;" << config.getValue("height") << std::endl
			<< "cooperateCost;" << config.getValue("cooperateCost") << std::endl
			<< "synergyFactor;" << config.getValue("synergyFactor") << std::endl
			<< "punishmentCost;" << config.getValue("punishmentCost") << std::endl
			<< "punishmentFine;" << config.getValue("punishmentFine") << std::endl
			<< "matchupType;" << config.getValue("matchupType") << std::endl
			<< "selectorType;" << config.getValue("selectorType") << std::endl
			<< "repopulatorType;" << config.getValue("repopulatorType") << std::endl
            << "gridType;" << config.getValue("gridType") << std::endl
            << "payoffType;" << config.getValue("payoffType") << std::endl
            << "mutatorType;" << config.getValue("mutatorType") << std::endl
			<< "mutationRate;" << config.getValue("mutationRate") << "%" << std::endl
			<< "showAllGenerations;" << config.getValue("showAllGenerations") << std::endl
			<< "archiveData;" << config.getValue("archiveData") << std::endl
			<< "visualize;" << config.getValue("visualize") << std::endl
			<< "folderName;" << config.getValue("folderName") << std::endl
			<< "logSuffix;" << config.getValue("logSuffix") << std::endl
			<< "timeToFile;" << config.getValue("timeToFile") << std::endl
			<< "timeToFolder;" << config.getValue("timeToFolder") << std::endl
			<< "consoleOutExponent;" << config.getValue("consoleOutExponent");
    }

    void ConfigArchiver::archive(const std::string & line)
    {
        m_fileHandle << line << std::endl;
    }
	void ConfigArchiver::configure(Config& config)
	{
		m_folderName = config.getValue("folderName");
		applyTimestampToFolder(stoi(config.getValue("timeToFolder")));
		m_fileSuffix = config.getValue("logSuffix");
		applyTimestampToFile(stoi(config.getValue("timeToFile")));
	}
}