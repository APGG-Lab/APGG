#pragma once
#include <array>
#include <string>
#include <unordered_map>
#include <iostream>

namespace APGG {

	/**
	* Keeps data for the Configurable interface. Data entries are related to a string key and accessable through them. 
	* Also holds and provides an id for the config to be able to see current configuration during execution.
	*/
	class Config
	{
	public:
		std::string getValue(const std::string& key, const std::string& alternative = "");
		std::unordered_map<std::string, std::string>& getMapReference();
		Config();
		Config(const unsigned int id);
		unsigned int getID() const;
	private:
		unsigned int m_id = 0;
		std::unordered_map<std::string, std::string> m_configMap;
	};
}
