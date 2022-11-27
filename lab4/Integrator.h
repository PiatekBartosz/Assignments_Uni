#pragma once
#include "IThread.h"
#include <vector>
#include <mutex>


class Integrator : public IThread {
public:
	enum Status {
		IDLE,
		WORKING
	};
private:
	Status status;
	std::vector<double> data;
	double step;
	double result;
	std::mutex dataMutex;
	std::mutex statusMutex;
	std::mutex resultMutex;
	void SetStatus(Status);
	void ThreadRoutine() override;
public:
	Integrator();
	void Count(const std::vector<double>&, const double);
	Status GetStatus();
	double GetResult();
};