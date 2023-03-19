#pragma once

#include <string>
#include <vector>
#include <sstream>
#include <fstream>

#include "Config.h"

namespace APGG {

	/**
	* Basic csv parser that produces a usable Config for the Configurable interface.
	*/
	class ConfigParserCSV
	{
	public:
		static std::vector<Config> parseConfigs(const std::string& filePath);
	};
}

