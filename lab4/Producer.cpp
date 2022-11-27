#include "Producer.h"

Producer::Producer() : IThread() {
}

Producer::~Producer() {
	Stop();
}


void Producer::ThreadRoutine(){
	while (isRunning()) {
		mutexP.lock();
		data.push_back(rand());
		mutexP.unlock();
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
}

std::vector<double> Producer::GetVector()
{
	std::vector<double> temp;
	mutexP.lock();
	temp = data;
	mutexP.unlock();
	return temp;
}
