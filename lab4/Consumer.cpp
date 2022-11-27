#include "Consumer.h"


Consumer::Consumer(Producer* ptr): ptr(ptr), avg(0)
{
}


void Consumer::ThreadRoutine()
{
	while(isRunning()) {
		std::vector<double> data = ptr->GetVector();
		size_t data_size = data.size();
		double sum = 0;
		for (int i = 0; i < data_size; i++) {
			sum += data[i];
		}
		sum /= data_size;
		mutexC.lock();
		avg = sum;
		mutexC.unlock();
		
	}
	std::this_thread::yield();
}

double Consumer::GetAvg()
{
	double temp;
	mutexC.lock();
	temp = avg;
	mutexC.unlock();
	return temp;
}
