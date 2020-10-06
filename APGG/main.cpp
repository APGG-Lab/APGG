#include <iostream>
#include <string>
#include <thread>
#include <vector>
#include <future>
#include <algorithm>

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
}

int main(int argc, char * argv[]) 
{
	auto configs = ConfigParserCSV::parseConfigs("configs.csv");
    std::cout << "[APGG Init] loading " << configs.size() << " experiments\n";

	int threadCount = 1;
	if (argc == 2) 
	{
		threadCount = std::stoi(argv[1]);
		if (threadCount < 1) 
		{
			std::cout << "[APGG Error] Invalid number of threads. Threadcount must be >=1 (actual value: " << std::to_string(threadCount) << ")";
			std::cin.get();
			std::quick_exit(1);
		}
	}

	using namespace std::chrono_literals;
	//TODO: make configurable
	unsigned int concurentNumberThreads = static_cast<unsigned int>(threadCount);
	if (concurentNumberThreads > static_cast<unsigned int>(configs.size()))
	{
		concurentNumberThreads = static_cast<unsigned int>(configs.size());
	}

	std::cout << "[APGG Init] Using " << std::to_string(concurentNumberThreads) << " threads\n";

	std::vector<std::future<void>> threadFutures;

	for (unsigned int i = 0; i < concurentNumberThreads; i++)
	{
		threadFutures.push_back(std::async(std::launch::async, RunExperiment, configs[i]));
	}

	unsigned int nextThread = concurentNumberThreads;
	unsigned int numberTasks = static_cast<unsigned int>(configs.size());
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

	return 0;
}

