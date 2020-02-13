#include "Config.h"

namespace APGG {

	std::string Config::getValue(std::string key, std::string alternative)
	{
		std::unordered_map<std::string, std::string>::iterator i = m_configMap.find(key);

		if (i == m_configMap.end())
		{
			//not found
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

	Config::Config() : m_id(0)
	{
	}

	Config::Config(const unsigned int id) : m_id(id)
	{
	}

	unsigned int Config::getID() const
	{
		return m_id;
	}

}