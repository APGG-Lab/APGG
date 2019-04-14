#include <iostream>
#include <chrono>
#include "World.h"

typedef std::chrono::high_resolution_clock HighResClock;
typedef std::chrono::milliseconds ms;
typedef std::chrono::duration<double> fsec;

int main() {	
	World myCoolWorld;
    myCoolWorld.Init();

    auto t_start = HighResClock::now();
    auto t_last = HighResClock::now();
    auto t_now = HighResClock::now();
    fsec fs;
    ms timeDelta;
    int exponent = 10;

    while (myCoolWorld.m_generation < 10000)
    {

        myCoolWorld.Tick();
        myCoolWorld.Evolve();

        if (myCoolWorld.m_generation > exponent - 1) {
            t_now = HighResClock::now();
            fs = t_now - t_start;
            t_last = t_now;
            timeDelta = std::chrono::duration_cast<ms>(fs);

            exponent *= 10;

            std::cout << "Num of Gen: " << myCoolWorld.m_generation
                      << " took " <<  timeDelta.count() << "ms" << std::endl;
        }

	}

    myCoolWorld.Fini();

    fs = t_now - t_start;
    timeDelta = std::chrono::duration_cast<ms>(fs);

    std::cout << "Done (took " << timeDelta.count() << " ms)";
    getchar();
	return 0;
}