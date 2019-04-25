#include "Config.h"

Config::Config()
{

}

Config& Config::getInstance()
{
	static Config instance;
	return instance;
}
