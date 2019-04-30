#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

#include "World.h"

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
	auto configs = parseCSV<11>("configs.csv");
	for (auto config : configs)
	{
		Config::getInstance().numGenerations = stoi(config[0]);
		Config::getInstance().eliminationCount = stoi(config[1]);
		Config::getInstance().groupSize = stoi(config[2]);
		Config::getInstance().width = stoi(config[3]);
		Config::getInstance().height = stoi(config[4]);
		Config::getInstance().synergyFactor = stoi(config[4]);
		Config::getInstance().punishmentCost = stoi(config[5]);
		Config::getInstance().punishmentFine = stoi(config[6]);
		Config::getInstance().matchupType = stoi(config[7]);
		Config::getInstance().showAllGenerations = stoi(config[8]);
		Config::getInstance().archiveData = stoi(config[9]);
		Config::getInstance().visualize = stoi(config[10]);
		

		World myCoolWorld;
		myCoolWorld.Init();

		while (myCoolWorld.m_generation < stoi(config[0]))
		{

			myCoolWorld.Tick();
			myCoolWorld.Evolve();
		}

		myCoolWorld.Fini();

		getchar();
		if (Config::getInstance().visualize)
			system("python3 Visualize.py");
		
	}
	getchar();
	return 0;
}

