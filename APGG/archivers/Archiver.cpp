#include "Archiver.h"

namespace APGG {

    std::string Archiver::getTimestamp()
    {
        std::time_t t = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        std::tm buf;
        localtime_s(&buf, &t);

        //@todo find a better way to return the put_time dateobject
        std::stringstream ss;
        ss << std::put_time(&buf, "%Y_%m_%d_%H_%M_%S");
        return ss.str();
    }

    Archiver::Archiver() : m_folderName(""), m_fileSuffix(""), m_header(""), m_appendTimestampToFile(true), m_appendTimestampToFolder(true)
    {
    }

    Archiver::Archiver(const std::string& folderName, const std::string& fileSuffix) : m_folderName(folderName), m_fileSuffix(fileSuffix), m_header(""),m_appendTimestampToFile(false), m_appendTimestampToFolder(true)
    {
    }

    void Archiver::setFolderName(const std::string & folderName)
    {
        m_folderName = folderName;
    }

    void Archiver::setFileStuffix(const std::string & fileSuffix)
    {
        m_fileSuffix = fileSuffix;
    }

    void Archiver::setHeader(const std::string & header)
    {
        m_header = header;
    }

    void Archiver::open()
    {
        std::string baseFolderName = "experiments/";
        std::string fullFolderName = baseFolderName + m_folderName;
        if (m_appendTimestampToFolder) 
        {
            fullFolderName += ("_" + getTimestamp());
        }
        fullFolderName += "/";

        if (!fs::is_directory(baseFolderName) || !fs::exists(baseFolderName))
        { // Check if base folder exists
            fs::create_directory(baseFolderName); // create src folder
            std::cout << "[Archiver] created folder: " << baseFolderName << "\n";
        }

        if (!fs::is_directory(fullFolderName) || !fs::exists(fullFolderName)) 
        { // Check if src folder exists
            fs::create_directory(fullFolderName); // create src folder
            std::cout << "[Archiver] created folder: " << fullFolderName << "\n";
        }

        std::string fullFileName = m_fileBaseName;
        fullFileName += ("_" + m_fileSuffix);

        if (m_appendTimestampToFile) 
        {
            fullFileName += ("_" + getTimestamp());
        }

        fullFileName += ".csv";

        m_fileHandle.open(fullFolderName + fullFileName);
        m_fileHandle << m_header << "\n";

        m_fullFileName = fullFolderName + fullFileName;
    }

    void Archiver::close()
    {
        m_fileHandle.close();
    }

    void Archiver::archive()
    {
        m_fileHandle << "TEST\n";
    }


    void Archiver::applyTimestampToFile(const bool & status)
    {
        m_appendTimestampToFile = status;
    }

    void Archiver::applyTimestampToFolder(const bool & status)
    {
        m_appendTimestampToFolder = status;
    }

    std::string Archiver::getFullFilename() const
    {
        return m_fullFileName;
    }

    Archiver::~Archiver()
    {
    }

}
