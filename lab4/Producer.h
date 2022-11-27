#pragma once
#include "IThread.h"
#include <vector>
#include <mutex>
#include <random>
class Producer : public IThread
{
	std::vector<double> data;
	std::mutex mutexP;
public:
	Producer();
	~Producer();
	void ThreadRoutine() override;
	std::vector<double> GetVector();
};

