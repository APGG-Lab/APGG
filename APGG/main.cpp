#include <iostream>
#include "World.h"



int main() {	
	World myCoolWorld;
	
	while (myCoolWorld.m_generation < 10000)
	{
		std::cout << "Num of Gen: " << myCoolWorld.m_generation;
		myCoolWorld.Tick();
		myCoolWorld.Evolve();



	}
	std::cout << "Done";
	getchar();
	return 0;
}
