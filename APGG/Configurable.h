#pragma once

#include "Config.h"

namespace APGG {

	/**
	* Basic interface to force all inheriting classes to be able to parse information from the config.
	*/
	class Configurable
	{
	public:
		virtual void configure(Config& config) = 0;
	};
}
