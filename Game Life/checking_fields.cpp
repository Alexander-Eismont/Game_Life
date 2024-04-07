#include <string>
#include <iostream>

// проверка двух полей (страрого (предыдущего) и нового) на одинаковость
// и если они одинаковые, то "жизнь" перешла в стагнацию
bool isLifeStagnated(char** current_gen, char** next_gen, const int& rows, const int& columns, std::string& result)
{
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < columns; j++)
		{
			// проверка на одинаковые ячейки у старого и нового полей
			if (next_gen[i][j] != current_gen[i][j])
				return true;
			else
				// возврат строки через ссылку (или указатель) с выводом
				result = "The world has stagnated. Game Over.\n";
		}

	return false;
}

// проверка (подсчет) количества "живых" элементов на поле
bool isNumberOfLiving(char** field, const int& rows, const int& columns, int& count_living, std::string& result)
{
	int count = 0;

	// считаем "живые" клетки на поле
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < columns; j++)
			if (field[i][j] == '*')
				count++;

	// по ссылке передается количество живых клеток для вывода информации
	count_living = count;

	// если "живых" клеток на поле нету, то возвращается false и цикл печати
	// элементов останавливается и через передачу по ссылке (или указателю)
	// возвращается строка с выводом
	if (count == 0)
	{
		// по ссылке в переменную передается итоговый вывод
		result = "There are no \"living\" cells left on the field.\n";
		return false;
	}

	return true;
}