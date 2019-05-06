#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

#include "World.h"

using namespace APGG;

template <size_t ColumnNumber> std::vector<std::array<std::string, ColumnNumber>> parseCSV(std::string filePath)
{
	std::vector<std::array<std::string, ColumnNumber>> output;

	// File pointer 
	std::ifstream fin;

	// Open an existing file 
	fin.open(filePath);

	// Read the Data from the file 
	// as String Vector 
	std::vector<std::string> row;
	std::string line, word;

	// Skip the first line, which details the content of the columns
	{
		std::getline(fin, line);
	}

	if (!fin.is_open())
	{
		// error message system here 
		return output;
	}

	while (std::getline(fin, line)) {

		std::array<std::string, ColumnNumber> row;
		row.fill("");

		// used for breaking words 
		std::istringstream ss(line);

		int i = 0;
		// getline only continues if there is still something to parse
		while (i < ColumnNumber && std::getline(ss, word, ';')) {
			//std::cout << word << std::endl;

			// is this inefficent? should the getline write into the array index immediatley?
			row[i] = word;
			i++;
		}

		output.push_back(std::move(row));
	}

	return output;
}

int main() {
	auto configs = parseCSV<20>("configs.csv");
    std::cout << "[APGG Init] loading " << configs.size() << " experiments" << std::endl;

	for (auto config : configs)
	{
        int i = 0;
        Config::getInstance().numGenerations = stoi(config[i++]);
		Config::getInstance().eliminationCount = stoi(config[i++]);
		Config::getInstance().groupSize = stoi(config[i++]);
		Config::getInstance().width = stoi(config[i++]);
		Config::getInstance().height = stoi(config[i++]);
		Config::getInstance().cooperateCost = stoi(config[i++]);
		Config::getInstance().synergyFactor = stoi(config[i++]);
		Config::getInstance().punishmentCost = stoi(config[i++]);
		Config::getInstance().punishmentFine = stoi(config[i++]);
		Config::getInstance().matchupType = stoi(config[i++]);
        Config::getInstance().selectorType = stoi(config[i++]);
        Config::getInstance().repopulatorType = stoi(config[i++]);
		Config::getInstance().showAllGenerations = stoi(config[i++]);
		Config::getInstance().archiveData = stoi(config[i++]);
		Config::getInstance().visualize = stoi(config[i++]);
        Config::getInstance().folderName = config[i++];
        Config::getInstance().logSuffix = config[i++];
        Config::getInstance().timeToFile = stoi(config[i++]);
        Config::getInstance().timeToFolder = stoi(config[i++]);
        Config::getInstance().consoleOutExponent = stoi(config[i++]);

		World myCoolWorld;
		myCoolWorld.Init();

		while (myCoolWorld.m_generation < stoi(config[0]))
		{

			myCoolWorld.Tick();
			myCoolWorld.Evolve();
		}

		myCoolWorld.Fini();

        if (configs.size() == 1 && Config::getInstance().visualize) {
            system("python3 Visualize.py");
        }
		
	}
	getchar();
	return 0;
}

