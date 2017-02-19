#include <iostream>
#include <windows.h>
#include <exception>

using namespace std;

double getResultDivisionPolynoms(int* firstArrayOfParameters, int* secondArrayOfParameters)
{
	int size1 = firstArrayOfParameters[0];
	int size2 = secondArrayOfParameters[0];
	int numerator = firstArrayOfParameters[size1 - 1];
	int denominator = secondArrayOfParameters[size2 - 1];

	if (denominator == 0)
		throw exception("Значение полинома-знаменателя равно 0!");
	else
		return ((double)numerator / (double)denominator);
}