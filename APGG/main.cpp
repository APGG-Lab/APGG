#include <iostream>
#include <string>
#include <thread>
#include <vector>
#include <future>

#include "World.h"
#include "ConfigParserCSV.h"

using namespace APGG;

void RunExperiment(Config config)
{
	World myCoolWorld;
	myCoolWorld.Init(config);

	while (myCoolWorld.m_generation < static_cast<unsigned int>(stoi(config.getValue("numGenerations", "10"))))
	{

		myCoolWorld.Tick();
		myCoolWorld.Evolve();
	}

	myCoolWorld.Fini();


	if (stoi(config.getValue("visualize", "0")) && false) {
		//todo find better way to open the python script automatically
		system("python3 Visualize.py");
	}
}

int main() {
	auto configs = ConfigParserCSV::parseConfigs("configs.csv");
    std::cout << "[APGG Init] loading " << configs.size() << " experiments" << std::endl;



	using namespace std::chrono_literals;
	//TODO: make configurable
	unsigned int concurentNumberThreads = 16;
	if (concurentNumberThreads > configs.size())
	{
		concurentNumberThreads = configs.size();
	}

	std::vector<std::future<void>> threadFutures;

	for (int i = 0; i < concurentNumberThreads; i++)
	{
		threadFutures.push_back(std::async(std::launch::async, RunExperiment, configs[i]));
	}

	unsigned int nextThread = concurentNumberThreads;
	unsigned int numberTasks = configs.size();
	bool remainingTasks = numberTasks > concurentNumberThreads;

	while (remainingTasks)
	{
		for (auto& future : threadFutures)
		{
			if (future.wait_for(0ms) == std::future_status::ready)
			{
				//start new thread in case there is still work to be done
				if (nextThread < (numberTasks))
				{
					future = std::async(std::launch::async, RunExperiment, configs[nextThread]);
					nextThread++;
				}
				else
				{
					remainingTasks = false;
					break;
				}

			}
		}
	}

	//wait for all threads to be finished before the main thread closes
	bool allThreadsFinished = false;
	while (!allThreadsFinished)
	{
		allThreadsFinished = true;
		for (auto& future : threadFutures)
		{
			if (future.wait_for(0ms) != std::future_status::ready)
			{
				allThreadsFinished = false;
				break;
			}
		}
	}

	getchar();
	return 0;
}

