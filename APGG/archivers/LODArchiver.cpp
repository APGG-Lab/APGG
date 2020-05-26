#include "LODArchiver.h"


namespace APGG {

    LODArchiver::LODArchiver() : Archiver()
    {
        m_header = "payoff;faction;cooperated;moralist;nChildren;genomeC;genomeM";
        m_fileBaseName = "LOD";

    }

    LODArchiver::LODArchiver(const std::string & folderName, const std::string & fileSuffix) : Archiver(folderName, fileSuffix)
    {
        m_header = "payoff;faction;cooperated;moralist;nChildren;genomeC;genomeM";
       // m_header = "ID;generation;payoff;faction;cooperated;moralist;nChildren;genomeC;genomeM";
        m_fileBaseName = "LOD";
    }

    void LODArchiver::archive(Organism* organism)
    {

        m_fileHandle /*<< organism->ID << ";" */
                    /* << organism->m_generation << ";" */
                     << organism->m_payoff << ";"
                     << static_cast<unsigned int>(organism->m_faction) << ";"
                     << ((organism->m_cooperated) ? 1 : 0) << ";" 
                     << ((organism->m_moralist) ? 1 : 0) << ";" 
                     << organism->m_children.size() << ";" 
                     << organism->m_genomes[GENOME_COOPERATION].getValue() << ";" 
                     << organism->m_genomes[GENOME_MORALS].getValue()
                     << "\n";
    }

    void LODArchiver::archive(const std::string & line)
    {
        m_fileHandle << line << "\n";
    }
	void LODArchiver::configure(Config& config)
	{
		m_folderName = config.getValue("folderName");
		applyTimestampToFolder(stoi(config.getValue("timeToFolder")));
		m_fileSuffix = config.getValue("logSuffix");
		applyTimestampToFile(stoi(config.getValue("timeToFile")));
	}
}