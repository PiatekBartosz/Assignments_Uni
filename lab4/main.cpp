#include"RNG.h"
#include"Producer.h"
#include"Consumer.h"
#include<conio.h>


int main(void) {
	Producer producer1;
	Consumer consumer1(&producer1);
	producer1.Start();
	consumer1.Start();

	char ch = 'a';
	while(ch != 27) {
		ch = _getch();
		std::cout << consumer1.GetAvg() << std::endl;
	}
	for (size_t i = 0; i < 10; i++)
	{
		std::cout << "test";
	}
	
	return 0;
}