#pragma once

#include <iostream>
#include <string>
#include <iomanip>
#include <chrono>
#include <ctime>
#include <sstream>
#include <fstream>
#include <experimental/filesystem> // or #include <filesystem>
namespace fs = std::experimental::filesystem;

class Archiver
{
protected:
    std::string m_folderName;
    std::string m_fileSuffix;
    std::string m_header;
    bool m_appendTimestampToFile;
    bool m_appendTimestampToFolder;
    std::ofstream m_fileHandle;

    std::string getTimestamp();
public:
    Archiver();
    Archiver(const std::string& folderName, const std::string& m_fileSuffix);
    void setFolderName(const std::string& folderName);
    void setFileStuffix(const std::string& fileSuffix);
    void setHeader(const std::string& header);
    void open();
    void close();
    void archive();
    void applyTimestampToFile(const bool& status);
    void applyTimestampToFolder(const bool& status);
    ~Archiver();
};

