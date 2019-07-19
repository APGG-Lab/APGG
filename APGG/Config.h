#pragma once
#include <string>
#include <unordered_map>

namespace APGG {

	class Config
	{
	public:
		std::string getValue(std::string key, std::string alternative = "");
		std::unordered_map<std::string, std::string>& getMapReference();

	private:
		std::unordered_map<std::string, std::string> m_configMap;
	};
}