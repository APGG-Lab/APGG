#pragma once
#define __STDC_WANT_LIB_EXT1__ 1
#include <iostream>
#include <string>
#include <iomanip>
#include <chrono>
#include <ctime>
#include <sstream>
#include <fstream>
#include <filesystem>

#include "../Configurable.h"

namespace fs = std::filesystem;

#ifdef __unix__
#define localtime_s(x, y) localtime_r(y, x)
#endif

namespace APGG {

    /**
    * Base class for the archivers (classes that write to files). Keeps meta data of to write files and provides basic
    * functions for writing.
    */
    class Archiver : public Configurable
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

		virtual void configure(Config& config) = 0;
    };

}
