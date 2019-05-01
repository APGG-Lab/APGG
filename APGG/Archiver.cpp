#include "Archiver.h"


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

Archiver::Archiver() : m_folderName(""), m_fileSuffix(""), m_appendTimestampToFolder(true), m_appendTimestampToFile(true)
{
}

Archiver::Archiver(const std::string& folderName, const std::string& fileSuffix) : m_folderName(folderName), m_fileSuffix(fileSuffix), m_appendTimestampToFolder(true), m_appendTimestampToFile(false)
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
    std::string fullFolderName = "experiments/" + m_folderName;
    if (m_appendTimestampToFolder) {
        fullFolderName += ("_" + getTimestamp());
    }
    fullFolderName += "/";

    if (!fs::is_directory(fullFolderName) || !fs::exists(fullFolderName)) { // Check if src folder exists
        fs::create_directory(fullFolderName); // create src folder
        std::cout << "[Archiver] created folder: " << fullFolderName << std::endl;
    }

    std::string fullFileName = "score";
    if (m_appendTimestampToFile) {
        fullFileName += ("_" + getTimestamp());
    }
    fullFileName += ("_" + m_fileSuffix + ".csv");

    m_fileHandle.open(fullFolderName + fullFileName);
    m_fileHandle << m_header << std::endl;
}

void Archiver::close()
{
    m_fileHandle.close();
}

void Archiver::archive()
{
    m_fileHandle << "TEST" << std::endl;
}


void Archiver::applyTimestampToFile(const bool & status)
{
    m_appendTimestampToFile = status;
}

void Archiver::applyTimestampToFolder(const bool & status)
{
    m_appendTimestampToFolder = status;
}

Archiver::~Archiver()
{
}
