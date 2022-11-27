#include "Calculator.h"
#include <cmath>

Calculator::Calculator(): result(0.0) {

}

Calculator::~Calculator() {

}

void Calculator::Add(const double a, const double b) {
	result = a + b;
}

void Calculator::Sub(const double a, const double b) {
	result = a - b;
}

void Calculator::Multiply(const double a, const double b) {
	result = a * b;
}

Calculator::Error Calculator::Divide(const double a, const double b) {
	if (b == 0.0) {
		result = 0.0;
		return Error::DIVISION_BY_ZERO;
	}
	else {
		result = a / b;
		return Error::SUCCESS;
	}
}

const double Calculator::GetResult() {
	return result;
}

void Calculator::ResetValue(double x) {
	x = 0;
}

void Calculator::ResetReferencedValue(double& x) {
	x = 0;
}

Calculator::Error Calculator::Roots(const double a, const double b, const double c, double& x1, double& x2) {

	double delta = b * b - 4 * a * c;

	if(a == 0) {
		return Error::INVALID_PARAMETER;
	}
	else{
		if (delta > 0.0){
			x1 = (-b - sqrt(delta)) / (2 * a);
			x2 = (-b + sqrt(delta)) / (2 * a);
			return Error::TWO_ROOTS;
		}
		else if(delta == 0){
			x1 = x2 = (-b) / (2 * a);
			return Error::SINGLE_ROOT;
		}
		else{
			return Error::NO_ROOTS;
		}
	}
}

