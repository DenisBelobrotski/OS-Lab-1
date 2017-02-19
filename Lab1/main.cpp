#include <iostream>
#include <windows.h>
#include <exception>

using namespace std;

void input(int*, int*, int, int);
DWORD WINAPI polynomThread(LPVOID);
double getResultDivisionPolynoms(int*, int*);
void outputResult(double, int);

int main()
{
	int firstDegree = 0;
	int secondDegree = 0;
	

	setlocale(LC_ALL, "rus");

	cout << "Введите степень полинома-числителя (целое неотрицательное число):\n";
	cin >> firstDegree;
	cout << "Введите степень полинома-знаменателя (целое неотрицательное число):\n";
	cin >> secondDegree;

	int* firstArrayOfParameters = new int[firstDegree + 5];
	int* secondArrayOfParameters = new int[secondDegree + 5];

	try
	{
		if (firstDegree < 0 || secondDegree < 0)
			throw exception("Неверная степень полинома!");
		else
		{
			input(firstArrayOfParameters, secondArrayOfParameters, firstDegree, secondDegree);

			HANDLE numPolynomThread;
			DWORD IDNumPolynom;
			HANDLE denPolynomThread;
			DWORD IDDenPolynom;

			numPolynomThread = CreateThread(NULL, 0, polynomThread, (void*)firstArrayOfParameters, 0, &IDNumPolynom);
			if (numPolynomThread == NULL)
				return GetLastError();

			denPolynomThread = CreateThread(NULL, 0, polynomThread, (void*)secondArrayOfParameters, 0, &IDDenPolynom);
			if (denPolynomThread == NULL)
				return GetLastError();

			HANDLE* handles = new HANDLE[2];

			handles[0] = numPolynomThread;
			handles[1] = denPolynomThread;

			WaitForMultipleObjects(2, handles, TRUE, INFINITE);

			CloseHandle(numPolynomThread);
			CloseHandle(denPolynomThread);

			outputResult(getResultDivisionPolynoms(firstArrayOfParameters, secondArrayOfParameters), firstArrayOfParameters[2]);
			
			delete [] firstArrayOfParameters;
			delete [] secondArrayOfParameters;
			delete [] handles;
		}
	}
	catch (exception e)
	{
		cout << e.what() << endl;
	}

	return 0;
}