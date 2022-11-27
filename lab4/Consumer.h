#pragma once
#include "Producer.h"
#include <vector>
#include <mutex>
#include<iostream>

class Consumer : public IThread
{
private:
	Producer* ptr;
	double avg;
	std::mutex mutexC;

public:
	Consumer(Producer *);
	void ThreadRoutine() override;
	double GetAvg();
};

