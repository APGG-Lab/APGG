#pragma once
#include <string>
#include "Archiver.h"

class SimpleArchiver : public Archiver
{
public:
    SimpleArchiver();
    SimpleArchiver(const std::string& folderName, const std::string& fileSuffix);
    void archive(const int generation, const int nCooperators, const int nDefectors, const int nMoralists, const int Immoralist);
    void archive(const std::string& line);
};

