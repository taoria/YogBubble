#pragma once
#include <chrono>
using namespace std::chrono;
class Timer{
private:
	bool isRunning;
public:
	Timer();
	double GetMilisecondsElapsed();
	void Restart();
	bool Stop();
	bool Start();
#ifdef _WIN32
	time_point<steady_clock> start;
	time_point<steady_clock> stop;

#else
	time_point<system_clock> start;
	time_point<system_clock> stop;
#endif
};
