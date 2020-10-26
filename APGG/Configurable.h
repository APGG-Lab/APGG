#pragma once

#include "Config.h"

namespace APGG {
	class Configurable
	{
	public:
		virtual void configure(Config& config) = 0;
		virtual ~Configurable() = default;
	};
}
