#include "LODArchiver.h"


namespace APGG {

    LODArchiver::LODArchiver() : Archiver()
    {
        m_header = "ID;generation;payoff;faction;cooperated;moralist;nChildren";
        m_fileBaseName = "LOD";

    }

    LODArchiver::LODArchiver(const std::string & folderName, const std::string & fileSuffix) : Archiver(folderName, fileSuffix)
    {
        m_header = "ID;generation;payoff;faction;cooperated;moralist;nChildren";
        m_fileBaseName = "LOD";
    }

    void LODArchiver::archive(const pOrganism& organism)
    {

        m_fileHandle << organism->ID << ";" 
                     << organism->m_generation << ";" 
                     << organism->m_payoff << ";"
                     << organism->m_faction << ";"
                     << ((organism->m_cooperated) ? 1 : 0) << ";" 
                     << ((organism->m_moralist) ? 1 : 0) << ";" 
                     << organism->m_children.size() << ";" 
                     << std::endl;
    }

    void LODArchiver::archive(const std::string & line)
    {
        m_fileHandle << line << std::endl;
    }
}