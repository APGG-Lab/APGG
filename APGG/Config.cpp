#include "Config.h"

namespace APGG {

	std::string Config::getValue(const std::string& key, const std::string& alternative)
	{
		std::unordered_map<std::string, std::string>::iterator i = m_configMap.find(key);

		if (i == m_configMap.end())
		{
			//not found
			std::cout << "[APGG Warning] You requested a non existing config key \"" + key + "\". Using default: \"" + alternative << "\"\n";
			return alternative;
		}
		else
		{
			return i->second;
		}
	}

	std::unordered_map<std::string, std::string>& Config::getMapReference()
	{
		return m_configMap;
	}

	Config::Config() : m_id(0), m_configMap(25)
	{
	}

	Config::Config(const unsigned int id) : m_id(id), m_configMap(25)
	{
	}

	unsigned int Config::getID() const
	{
		return m_id;
	}

}