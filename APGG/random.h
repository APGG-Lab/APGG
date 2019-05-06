#pragma once
#include <random>

inline float getRandomFloat() {
	static thread_local std::mt19937 gen{ std::random_device{}() };
	static thread_local std::uniform_real_distribution<float> pick{ 0, 1 };
	return pick(gen);
}


inline int getRandomNumber() {
    thread_local std::mt19937 gen{ std::random_device{}() };
    thread_local std::uniform_int_distribution<int> pick{ 0, 99999 };
    return pick(gen);
}

