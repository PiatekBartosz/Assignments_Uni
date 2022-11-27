#pragma once
class Calculator
{
private:
	double result;

public:
	Calculator(); // Konstruktor

	~Calculator(); // Destruktor

	enum Error {
		SUCCESS,
		NO_ROOTS,
		SINGLE_ROOT,
		TWO_ROOTS,
		INVALID_PARAMETER,
		DIVISION_BY_ZERO
	};
	
	void Add(const double, const double);
	void Sub(const double, const double);
	void Multiply(const double, const double);
	
	Error Divide(const double, const double);

	const double GetResult();

	void ResetValue(double);
	void ResetReferencedValue(double&);

	Error Roots(const double a, const double b, const double c, double &x1, double &x2);
};

