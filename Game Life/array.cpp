#include <iostream>

// создание двумерного массива (массив для поля игры)
char** createArray(const int& rows, const int& columns)
{
	char** arr = new char* [rows] {};

	for (int i = 0; i < rows; i++)
		arr[i] = { new char[columns] {} };

	return arr;
}

// удаление двумерного массива и освобождение памяти
void deleteArray(char** arr, const int& rows)
{
	for (int i = 0; i < rows; i++)
		delete[] arr[i];

	delete[] arr;
}

// вывод поля на экран
void printArray(char** field, const int& rows, const int& columns)
{
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++)
			std::cout << field[i][j] << ' ';

		std::cout << '\n';
	}
}
