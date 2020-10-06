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
			<< "numGenerations;" << config.getValue("numGenerations") << "\n"
			<< "eliminationCount;" << config.getValue("eliminationCount") << "\n"
			<< "groupSize;" << config.getValue("groupSize") << "\n"
			<< "width;" << config.getValue("width") << "\n"
			<< "height;" << config.getValue("height") << "\n"
			<< "cooperateCost;" << config.getValue("cooperateCost") << "\n"
			<< "synergyFactor;" << config.getValue("synergyFactor") << "\n"
			<< "punishmentCost;" << config.getValue("punishmentCost") << "\n"
			<< "punishmentFine;" << config.getValue("punishmentFine") << "\n"
			<< "selectorType;" << config.getValue("selectorType") << "\n"
			<< "repopulatorType;" << config.getValue("repopulationType") << "\n"
			<< "gridType;" << config.getValue("gridType") << "\n"
			<< "payoffType;" << config.getValue("payoffType") << "\n"
			<< "mutatorType;" << config.getValue("mutatorType") << "\n"
			<< "mutationRate;" << config.getValue("mutationRate") << "%" << "\n"
			<< "folderName;" << config.getValue("folderName") << "\n"
			<< "logSuffix;" << config.getValue("logSuffix") << "\n"
			<< "timeToFile;" << config.getValue("timeToFile") << "\n"
			<< "timeToFolder;" << config.getValue("timeToFolder") << "\n";
    }

    void ConfigArchiver::archive(const std::string & line)
    {
        m_fileHandle << line << "\n";
    }
	void ConfigArchiver::configure(Config& config)
	{
		m_folderName = config.getValue("folderName");
		applyTimestampToFolder(stoi(config.getValue("timeToFolder")));
		m_fileSuffix = config.getValue("logSuffix");
		applyTimestampToFile(stoi(config.getValue("timeToFile")));
	}
}