#include "Timer.h"
Timer::Timer(){
	
}

double Timer::GetMilisecondsElapsed(){
	if(isRunning){
		auto elapsed = duration<double, std::milli>(high_resolution_clock::now() - start);
		return elapsed.count();
	}else{
		auto elapsed = duration<double, std::milli>(stop - start);
		return elapsed.count();
	}
}

void Timer::Restart(){
	isRunning = true;
	start = high_resolution_clock::now();
}

bool Timer::Stop(){
	if(isRunning==true){
		isRunning = false;
		return false;

	}else{
		stop = high_resolution_clock::now();
		isRunning = false;
		return true;
	}
}

bool Timer::Start(){
	if(!isRunning){
		return false;
	}else{
		start = high_resolution_clock::now();
		isRunning = true;
		return true;
	}

}

