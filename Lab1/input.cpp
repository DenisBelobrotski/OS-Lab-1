#include <iostream>
#include <windows.h>
#include <exception>

using namespace std;

void input(int* firstArrayOfParameters, int* secondArrayOfParameters, int firstDegree, int secondDegree)
{
	int argument = 0;
	int tmp = 0;
	int size1 = firstDegree + 5;
	int size2 = secondDegree + 5;
	firstArrayOfParameters[0] = size1;
	secondArrayOfParameters[0] = size2;
	firstArrayOfParameters[1] = firstDegree;
	secondArrayOfParameters[1] = secondDegree;

	cout << "Введите значение аргумента:\n";
	cin >> argument;

	firstArrayOfParameters[2] = argument;
	secondArrayOfParameters[2] = argument;

	cout << "Введите коэффициенты полинома-числителя:\n";

	for (int i = 3; i < size1 - 1; i++)
	{
		cin >> tmp;
		firstArrayOfParameters[i] = tmp;
	}

	cout << "Введите коэффициенты полинома-знаменателя:\n";

	for (int i = 3; i < size2 - 1; i++)
	{
		cin >> tmp;
		secondArrayOfParameters[i] = tmp;
	}
}

