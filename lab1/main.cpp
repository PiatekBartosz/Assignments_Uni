#include <iostream>
#include "Calculator.h"


int main(void) {

	double x1, x2;

	Calculator calc;

	calc.Add(2, 2);
	std::cout << calc.GetResult() << std::endl;
	
	calc.Sub(2, 2);
	std::cout << calc.GetResult() << std::endl;
	
	calc.Multiply(2, 2);
	std::cout << calc.GetResult() << std::endl;
	
	calc.Divide(2, 0);
	std::cout << calc.Divide(2, 0) << std::endl;
	
	calc.Roots(1, -1, -2, x1, x2);
	std::cout << "x1:" << x1 << "x2:" << x2 << std::endl;
	std::cout << calc.Roots(1, 4, 4, x1, x2) << "x1:" << x1 << "x2:" << x2 << std::endl;
	std::cout << calc.Roots(0, 0, 0, x1, x2);
	
	if (calc.Roots(2, -4, 5, x1, x2) == Calculator::Error::TWO_ROOTS) {
		std::cout << "x1:" << x1 << "x2:" << x2 << std::endl;
	}
	else if(calc.Roots(1, 0, 5, x1, x2) == Calculator::Error::SINGLE_ROOT){
		std::cout << "x:" << x1 << std::endl;
	}
	else if(calc.Roots(2, 0, 5, x1, x2) == Calculator::Error::NO_ROOTS) {
		std::cout << "No roots!" << std::endl;
	}
	else {
		std::cout << "Invalid parameters!" << std::endl;
	}
	return 0;
}