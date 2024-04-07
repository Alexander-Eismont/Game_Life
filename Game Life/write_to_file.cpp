#include <iostream>
#include <fstream>
#include <ctime>

// получение числа от пользователя (размер поля (строки и столбцы) и количетво живых клеток)
int getNumFromUser()
{
	int num;
	std::cin >> num;

	return num;
}

// проверка на правильность ввода данных
bool checkingUserData(const int& lines, const int& columns, const int& living_cells)
{
	// расчет общей площади (количества клеток поля)
	int area = lines * columns;

	// неверное количество строк
	if (lines < 1)
	{
		std::cout << "Количество строк не может быть меньше или равно 0. Поле должно быть заполнено!\n";
		return false;
	}
	// неверное количество столбцов
	else if (columns < 1)
	{
		std::cout << "Количество столбцов не может быть меньше или равно 0. Поле должно быть заполнено!\n";
		return false;
	}
	// неверное количество живых ячеек
	else if ((living_cells < 0) || (living_cells > area))
	{
		std::cout << "Количество живых клеток не можеть быть меньше 0 и больше " << area << "\n";
		return false;
	}

	return true;
}

// получение рандомного числа для заполнения поля
// в size передается как количество строк, так и количество столбцов поля
// -1, т.к. минимальный индекс поля = 0, иначе нулевой индекс нельзя получить
int getRandomNum(const int size) { return (-1 + std::rand() % (-1 - size) + 1); }

// запись в файл размера поля от пользователя, а также координаты живых клеток
// в количестве, определенном пользователем, через рандомную генерацию
void writeToFile(const std::string& filename)
{
	// открытие файла
	std::ofstream file(filename);

	// проверка на открытие файла
	if (!file.is_open())
	{
		std::cout << "Не удалось открыть файл для записи.\n";
		return;
	}
	else
	{
		// количество строк и столбцов от пользователя
		std::cout << "Количество строк: ";
		int lines = getNumFromUser();
		std::cout << "Количество столбцов: ";
		int columns = getNumFromUser();

		// количество живых клеток от пользователя
		printf("Введите количество живых клеток в пределах от 0 до %d: ", lines * columns);
		int living_cells = getNumFromUser();

		// если данные введены корректно, то файл заполняется данными
		if (checkingUserData(lines, columns, living_cells))
		{
			// запись в файл количества строк и столбцов от пользователя
			file << lines << " " << columns << "\n";

			// запись в файл рандомного номера строки и столбца живой клетки
			// количество клеток определяется пользователем (возможна перезапись клеток)
			for (int i = 0; i < living_cells; i++)
			{
				// -1 - т.к. отсчет индекса поля начинается с 0 и если не прописать -1, то создание
				// клеток будет выходить за пределы поля (например, если размер поля 10х10, то максмальный индекс =9)
				int line_number = getRandomNum(lines - 1);
				int column_number = getRandomNum(columns - 1);

				// если это не последняя запись в файл, то в конце идет перенос строки
				// а если последняя запись, то перенос строки отсутствует
				(i < living_cells - 1) ? file << line_number << " " << column_number << "\n" :
					file << line_number << " " << column_number;
			}
		}
	}

	// закрытие файла
	file.close();
}
