#pragma once

#ifdef _DEBUG
#include <chrono>
#include <string>
#define DebugReturn(x) auto begin{ std::chrono::high_resolution_clock::now() };\
	std::string ret{ x };\
	auto end { std::chrono::high_resolution_clock::now()};\
	return ret + std::to_string(std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count()) + " μs\n";
#else
#define DebugReturn(x) return x;
#endif