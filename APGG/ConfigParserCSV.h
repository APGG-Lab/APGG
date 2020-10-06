#pragma once

#include <string>
#include <vector>
#include <sstream>
#include <fstream>

#include "Config.h"

namespace APGG {

	class ConfigParserCSV
	{
	public:
		static std::vector<Config> parseConfigs(const std::string& filePath);
	};
}

