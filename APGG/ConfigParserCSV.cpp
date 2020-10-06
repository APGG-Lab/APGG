#include "ConfigParserCSV.h"

namespace APGG {
	std::vector<Config> ConfigParserCSV::parseConfigs(const std::string& filePath)
	{
		std::vector<Config> outputConfigVector;
		std::vector<std::string> configMapKeys;

		std::ifstream fin;
		fin.open(filePath);
		if (!fin.is_open())
			return outputConfigVector;

		std::string line, word;

		//parse value keys in config
		if (!std::getline(fin, line))
			return outputConfigVector;
		std::istringstream keyLine(line);

		while (std::getline(keyLine, word, ';')) 
		{
			configMapKeys.emplace_back(word);
		}

		unsigned int experiment_counter = 0;

		//parse config data rows
		while (std::getline(fin, line)) 
		{
			std::istringstream configDataLine(line);

			Config config(experiment_counter++);
			unsigned int rowIndex = 0;

			while (rowIndex < configMapKeys.size() && std::getline(configDataLine, word, ';')) 
			{
				config.getMapReference().insert(std::make_pair(configMapKeys[rowIndex], word));
				rowIndex++;
			}

			outputConfigVector.emplace_back(config);
		}

		return outputConfigVector;
	}
}