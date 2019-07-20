#include <iostream>
#include <string>
#include "World.h"
#include "ConfigParserCSV.h"

using namespace APGG;

int main() {
	constexpr unsigned int configColumnSize = 24;
	auto configs = ConfigParserCSV::parseConfigs("configs.csv");
    std::cout << "[APGG Init] loading " << configs.size() << " experiments" << std::endl;

	for (auto & config : configs)
	{
		World myCoolWorld;
		myCoolWorld.Init(config);

		while (myCoolWorld.m_generation < stoi(config.getValue("numGenerations", "10")))
		{

			myCoolWorld.Tick();
			myCoolWorld.Evolve();
		}

		myCoolWorld.Fini();

		
        if (configs.size() == 1 && stoi(config.getValue("visualize", "0")) && false) {
            //todo find better way to open the python script automatically
            system("python3 Visualize.py");
        }
		
		
	}
	getchar();
	return 0;
}

