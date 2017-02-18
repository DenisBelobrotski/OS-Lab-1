#include <iostream>
#include <windows.h>
#include <exception>
using namespace std;

void input(void**, void**, int, int);
void runThreads(void**, void**);
DWORD WINAPI polynom(LPVOID);
double easyPow(double, int);
double getResult(void**, void**);
void outputResult(double, double);

int main()
{
	setlocale(LC_ALL, "rus");
	int firstDegree = 0;
	int secondDegree = 0;
	cout << "Введите степень полинома-числителя (целое неотрицательное число):\n";
	cin >> firstDegree;
	cout << "Введите степень полинома-знаменателя (целое неотрицательное число):\n";
	cin >> secondDegree;
	void** firstArrayOfParameters = new void*[firstDegree + 5];
	void** secondArrayOfParameters = new void*[secondDegree + 5];
	try
	{
		if (firstDegree < 0 || secondDegree < 0)
			throw exception("Неверная степень полинома!");
		else
		{
			input(firstArrayOfParameters, secondArrayOfParameters, firstDegree, secondDegree);
			runThreads(firstArrayOfParameters, secondArrayOfParameters);
			outputResult(getResult(firstArrayOfParameters, secondArrayOfParameters), *(double*)firstArrayOfParameters[2]);
		}
	}
	catch (exception e)
	{
		cout << e.what() << endl;
	}
	return 0;
}

void input(void** firstArrayOfParameters, void** secondArrayOfParameters, int firstDegree, int secondDegree)
{
	double argument = 0;
	double tmp = 0;
	int size1 = firstDegree + 5;
	int size2 = secondDegree + 5;
	firstArrayOfParameters[0] = new int(size1);
	secondArrayOfParameters[0] = new int(size2);
	firstArrayOfParameters[1] = new int(firstDegree);
	secondArrayOfParameters[1] = new int(secondDegree);
	cout << "Введите значение аргумента:\n";
	cin >> argument;
	firstArrayOfParameters[2] = new double(argument);
	secondArrayOfParameters[2] = new double(argument);
	cout << "Введите коэффициенты полинома-числителя:\n";
	for (int i = 3; i < size1 - 1; i++)
	{
		cin >> tmp;
		firstArrayOfParameters[i] = new double(tmp);
	}
	cout << "Введите коэффициенты полинома-знаменателя:\n";
	for (int i = 3; i < size2 - 1; i++)
	{
		cin >> tmp;
		secondArrayOfParameters[i] = new double(tmp);
	}
}

void runThreads(void** firstArrayOfParameters, void** secondArrayOfParameters)
{
	HANDLE numPolynomThread;
	DWORD IDNumPolynom;
	HANDLE denPolynomThread;
	DWORD IDDenPolynom;
	numPolynomThread = CreateThread(NULL, 0, polynom, (void*)firstArrayOfParameters, 0, &IDNumPolynom);
	denPolynomThread = CreateThread(NULL, 0, polynom, (void*)secondArrayOfParameters, 0, &IDDenPolynom);
	HANDLE* handles = new HANDLE[2];
	handles[0] = numPolynomThread;
	handles[1] = denPolynomThread;
	WaitForMultipleObjects(2, handles, TRUE, INFINITE);
	CloseHandle(numPolynomThread);
	CloseHandle(denPolynomThread);
}

DWORD WINAPI polynom(LPVOID parameter)
{
	void** arrayOfParameters = (void**)parameter;
	int size = *(int*)arrayOfParameters[0];
	int degree = *(int*)arrayOfParameters[1];
	double argument = *(double*)arrayOfParameters[2];
	double result = 0;
	cout << "Степень полинома:\n" << degree << endl;
	cout << "Коэффициенты полинома:\n";
	for (int i = 3; i < size - 1; i++)
	{
		cout << *(double*)arrayOfParameters[i] << " ";
		result += *(double*)arrayOfParameters[i] * easyPow(argument, degree);
		degree--;
		Sleep(17);
	}
	cout << endl << "p(" << argument << ") = " << result << endl;
	arrayOfParameters[size - 1] = new double(result);
	return 0;
}

double easyPow(double foundation, int index)
{
	double result = 1;
	if (index == 0)
		return result;
	else
	{
		for (int i = 0; i < abs(index); i++)
			result *= foundation;
		if (index < 0)
			return (1 / result);
		return result;
	}
}

double getResult(void** firstArrayOfParameters, void** secondArrayOfParameters)
{
	int size1 = *(int*)firstArrayOfParameters[0];
	int size2 = *(int*)secondArrayOfParameters[0];
	double numerator = *(double*)firstArrayOfParameters[size1 - 1];
	double denominator = *(double*)secondArrayOfParameters[size2 - 1];
	if (denominator == 0) 
		throw exception("Значение полинома-знаменателя равно 0!");
	else
	{
		return (numerator / denominator);
	}
}

void outputResult(double result, double argument)
{
	cout << "f(" << argument << ") = " << result << endl;
}