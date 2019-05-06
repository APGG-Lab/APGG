#include "SimpleArchiver.h"

SimpleArchiver::SimpleArchiver() : Archiver()
{
    m_header = "generation;nCooperators;nDefectors;nMoralists;nImmoralists";
}

SimpleArchiver::SimpleArchiver(const std::string & folderName, const std::string & fileSuffix) : Archiver(folderName, fileSuffix)
{
    m_header = "generation;nCooperators;nDefectors;nMoralists;nImmoralists";
}

void SimpleArchiver::archive(const int generation, const int nCooperators, const int nDefectors, const int nMoralists, const int nImmoralist)
{
    m_fileHandle << generation << ";" << nCooperators << ";" << nDefectors << ";" << nMoralists << ";" << nImmoralist << std::endl;
}

void SimpleArchiver::archive(const std::string & line)
{
    m_fileHandle << line << std::endl;
}