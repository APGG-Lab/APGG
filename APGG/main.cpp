#include <iostream>
#include <chrono>
#include "World.h"

typedef std::chrono::high_resolution_clock HighResClock;
typedef std::chrono::milliseconds ms;
typedef std::chrono::duration<double> fsec;

int main() {	
	World myCoolWorld;
	
    auto t_start = HighResClock::now();


	while (myCoolWorld.m_generation < 10000)
	{
		std::cout << "Num of Gen: " << myCoolWorld.m_generation;
		myCoolWorld.Tick();
		myCoolWorld.Evolve();



	}

    auto t_end = HighResClock::now();
    fsec fs = t_end - t_start;
    ms timeDelta = std::chrono::duration_cast<ms>(fs);

    std::cout << "Done (took " << timeDelta.count() << " ms)";
    getchar();
	return 0;
}