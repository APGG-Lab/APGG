#pragma once
#include <iostream>
#include <chrono>

#include "Grid.h"

typedef std::chrono::high_resolution_clock HighResClock;
typedef std::chrono::milliseconds ms;
typedef std::chrono::duration<double> fsec;


#include <fstream>

class World
{
private:
    std::chrono::time_point<std::chrono::steady_clock> m_clock_start;
    std::chrono::time_point<std::chrono::steady_clock> m_clock_now;
    std::chrono::time_point<std::chrono::steady_clock> m_clock_last;
    void printStatus();
    int m_exponent; ///Exponential logging (0-10,10,20,30,100,200,300,1000,2000,3000,....)

    unsigned int m_cooperation;
    float m_fitness;
public:
	World();

    void Init();
	void Tick();
    void Fini();

	void Evolve();
	void Archive(float fitness, int cooperation, int defectors);
	std::ofstream myfile;
	Grid m_grid;
	int m_generation = 0;
};

