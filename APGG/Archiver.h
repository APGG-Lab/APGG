#pragma once
#define __STDC_WANT_LIB_EXT1__ 1
#include <iostream>
#include <string>
#include <iomanip>
#include <chrono>
#include <ctime>
#include <sstream>
#include <fstream>
#ifdef __unix__
#include <filesystem>
namespace fs = std::filesystem;
#else
#include <experimental/filesystem> // or #include <filesystem>
namespace fs = std::experimental::filesystem;
#endif

#ifdef __unix__
#define localtime_s(x, y) localtime_r(y, x)
#endif

namespace APGG {

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
        std::string m_fullFileName; //@todo : better var name
        std::string m_fileBaseName = "score";
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
        std::string getFullFilename() const;
        ~Archiver();
    };

}
