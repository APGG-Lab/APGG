#pragma once
#include <array>
#include <string>
#include <unordered_map>
#include <iostream>

namespace APGG {

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
