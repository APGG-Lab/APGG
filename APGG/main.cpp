#include <iostream>

#include "World.h"


int main() {	
	World myCoolWorld;
    myCoolWorld.Init();

    while (myCoolWorld.m_generation < 10000)
    {

        myCoolWorld.Tick();
        myCoolWorld.Evolve();
	}

    myCoolWorld.Fini();

    getchar();
	return 0;
}