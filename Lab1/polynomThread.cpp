#include <iostream>
#include <windows.h>
#include <exception>

using namespace std;

DWORD WINAPI polynomThread(LPVOID parameter)
{
	int* arrayOfParameters = (int*)parameter;
	int size = arrayOfParameters[0];
	int degree = arrayOfParameters[1];
	int argument = arrayOfParameters[2];
	int result = 0;

	cout << "Степень полинома:\n" << degree << endl;
	cout << "Коэффициенты полинома:\n";

	for (int i = 3; i < size - 1; i++)
	{
		cout << arrayOfParameters[i] << " ";
		result += arrayOfParameters[i] * static_cast<int>(pow(argument, degree));
		degree--;
		Sleep(17);
	}

	cout << endl << "p(" << argument << ") = " << result << endl;

	arrayOfParameters[size - 1] = result;

	return 0;
}


