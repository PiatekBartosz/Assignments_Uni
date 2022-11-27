#include"integrator.h"
#include<iostream>

void Integrator::SetStatus(Status sta)
{
	statusMutex.lock();
	status = sta;
	statusMutex.unlock();
}

void Integrator::ThreadRoutine()
{
	if (GetStatus() == Status::WORKING) {
		dataMutex.lock();
		std::vector<double> tmpData = data;
		double tmpStep = step;
		dataMutex.unlock();

		double tmpResult = 0.0;

		for (int i = 0; i < tmpData.size(); i++){
			tmpResult += tmpData[i];
		}

		resultMutex.lock();
		result = tmpResult * tmpStep;
		resultMutex.unlock();

		SetStatus(Status::WORKING);
	}
	std::this_thread::yield;
}

Integrator::Integrator() : status(Status::IDLE), IThread(), result(0), step(0)
{
}

void Integrator::Count(const std::vector<double>& v, const double dt)
{	
	// status change at the end?
	if (status == Status::IDLE) {
		dataMutex.lock();
		data = v;
		step = dt;
		dataMutex.unlock();
		SetStatus(Status::WORKING);
	}
}

Integrator::Status Integrator::GetStatus()
{
	Status temp;
	statusMutex.lock();
	temp = status;
	statusMutex.unlock();
	return temp;
}

double Integrator::GetResult()
{
	double temp;
	resultMutex.lock();
	temp = result;
	resultMutex.unlock();
	return temp;
}
