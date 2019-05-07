#include <iostream>
#include <string>
#include "World.h"

using namespace APGG;



int main() {
	constexpr unsigned int configColumnSize = 20;
	auto configs = Config::parseCSV<configColumnSize>("configs.csv");
    std::cout << "[APGG Init] loading " << configs.size() << " experiments" << std::endl;

	for (auto config : configs)
	{
		Config::getInstance().setCurrentConfig<configColumnSize>(config);

		World myCoolWorld;
		myCoolWorld.Init();

		while (myCoolWorld.m_generation < stoi(config[0]))
		{

			myCoolWorld.Tick();
			myCoolWorld.Evolve();
		}

		myCoolWorld.Fini();

        if (configs.size() == 1 && Config::getInstance().visualize && false) {
            //todo find better way to open the python script automatically
            system("python3 Visualize.py");
        }
		
	}
	getchar();
	return 0;
}

