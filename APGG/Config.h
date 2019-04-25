#pragma once

class Config
{
public:
	// singleton
	static Config& getInstance();
	Config(Config const&) = delete;
	void operator=(Config const&) = delete;

	unsigned int numGenerations = 1000;
	unsigned int eliminationCount = 20;
	unsigned int groupSize = 1;
	unsigned int width = 32;
	unsigned int height = 32;
	unsigned int matchupType = 0;
	bool showAllGenerations = 0;
	bool logOutput = 1;
	bool visualize = 1;

private:
	Config();
};