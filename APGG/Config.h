#pragma once
#include <array>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>

namespace APGG {

    class Config
    {
    public:
        // singleton
        static Config& getInstance();
        Config(Config const&) = delete;
        void operator=(Config const&) = delete;

        unsigned int numGenerations = 1000;
        unsigned int eliminationCount = 20;
        unsigned int groupSize = 1;
        unsigned int width = 32;
        unsigned int height = 32;

        unsigned int cooperateCost = 1;
        unsigned int synergyFactor = 1;
        unsigned int punishmentCost = 1;
        unsigned int punishmentFine = 2;

        unsigned int matchupType = 0;
        unsigned int selectorType = 0;
        unsigned int repopulatorType = 0;
        unsigned int mutatorType = 0;
        unsigned int mutationRate = 0;


        bool showAllGenerations = 0;
        bool archiveData = 1;
        bool visualize = 1;

        std::string folderName = "";
        std::string logSuffix = "";
        bool timeToFile = 0;
        bool timeToFolder = 0;

        unsigned int consoleOutExponent = 10;

		template <size_t ColumnNumber> void setCurrentConfig(std::array<std::string, ColumnNumber> & currentConfig);
		template <size_t ColumnNumber> static std::vector<std::array<std::string, ColumnNumber>> parseCSV(std::string filePath);

    private:
        Config();
    };

	// template functions have to be defined in the header file if you do not include the .cpp also

	template <size_t ColumnNumber> void Config::setCurrentConfig(std::array<std::string, ColumnNumber>& config)
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
        Config::getInstance().mutatorType = stoi(config[i++]);
		Config::getInstance().mutationRate = stoi(config[i++]);
		Config::getInstance().showAllGenerations = stoi(config[i++]);
		Config::getInstance().archiveData = stoi(config[i++]);
		Config::getInstance().visualize = stoi(config[i++]);
		Config::getInstance().folderName = config[i++];
		Config::getInstance().logSuffix = config[i++];
		Config::getInstance().timeToFile = stoi(config[i++]);
		Config::getInstance().timeToFolder = stoi(config[i++]);
		Config::getInstance().consoleOutExponent = stoi(config[i++]);
	}

	template <size_t ColumnNumber> std::vector<std::array<std::string, ColumnNumber>> Config::parseCSV(std::string filePath)
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
}
