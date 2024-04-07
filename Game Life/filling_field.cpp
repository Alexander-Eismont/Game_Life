#include <iostream>
#include <fstream>

#include "array.h"

// создание поля только с "мертвыми" элементами
void createField(char** field, const int& rows, const int& columns)
{
	// наполнение массива "мертвыми" элементами
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < columns; j++)
			field[i][j] = '-';
}

// наполнение поля живыми элементами согласно данным из файла
void fillFieldWithLivingElements(const std::string& filename, char** field)
{
	std::ifstream file(filename);

	// пропуск первых двух чисел из файла, обозначающих размеры поля
	int size;
	file >> size >> size;

	// переменные для записи номера строки и столбца с "живым" элементом из файла
	int row, column;

	// наполнение поля "живыми" элементами
	while (file >> row >> column)
		field[row][column] = '*';

	file.close();
}

// расчет количества живых клеток вокруг ячейки
// rows и columns нужны, чтобы проверить выход за границы
// row и col - координаты текущей живой клетки
int calcNumOfLivingAroundCell(char** field, const int& rows, const int& columns, int& row, int& col)
{
	int num_of_living = 0;

	// зная координаты ячейки, проходимся циклами только по ячейкам вокруг
	// заданной, увеличив и уменьшив заданные координаты на 1, предусмотрев в
	// условии выход за пределы поля
	for (int i = row - 1; i <= row + 1; i++)
		for (int j = col - 1; j <= col + 1; j++)
		{
			// если выход за пределы поля, то пропускаем значения
			if ((i < 0) || (j < 0) || (i > rows - 1) || (j > columns - 1))
				continue;

			// подсчет количества живых клеток, вокруг ячейки
			if (field[i][j] == '*')
				num_of_living++;
		}

	// если изначально ячейка содержала живую клетку, то уменьшаем общее
	// количество найденных на 1, т.к. необходимо посчитать количество именно
	// вокруг ячейки
	if (field[row][col] == '*')
		num_of_living--;

	return num_of_living;
}

// функция создает и возвращает новый массив со старыми, новыми "живыми" или
// "мертвыми" клетками
void deathAndNewLifeCell(char** field, char** after_generation_field, const int& rows, const int& columns)
{
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < columns; j++)
		{
			after_generation_field[i][j] = field[i][j];

			// расчет количества живых клеток вокруг находящейся в данный момент
			int count = calcNumOfLivingAroundCell(field, rows, columns, i, j);

			// если вокруг живой клетки количество живых меньше 2 или больше 3,
			// то живая клетка "умирает"
			if (count < 2 || count > 3)
				//field[i][j] = '-';
				after_generation_field[i][j] = '-';

			// если клетка не живая и вокруг есть 3 живые клетки, то в текущей
			// создается новая "жизнь"
			if (count == 3 && field[i][j] != '*')
				//field[i][j] = '*';
				after_generation_field[i][j] = '*';
		}
}

// копирование в массив со старым полем сгенерированное новое поле
void copyField(char** field, char** after_generation_field, const int& rows, const int& columns)
{
	// копирование/обновление элементов поля после генерации в массив (поле) 
	// до генерации (предыдущей генерации)
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < columns; j++)
			field[i][j] = after_generation_field[i][j];
}