#include <chrono>  // milliseconds
#include <cstdlib> // для std::system("cls")
#include <fstream> // для работы с файлами
#include <iostream>
#include <thread> // this_thread, sleep_for()

#include "array.h"
#include "checking_fields.h"
#include "filling_field.h"
#include "write_to_file.h"

int game();
void printResult(char** field, char** after_generation_field, const int& rows, const int& columns);
void clearConsole();

int main()
{
    // установка значения системных часов в качестве стартового числа для рандомной генерации
    std::srand(static_cast<unsigned int>(std::time(0)));

    setlocale(LC_ALL, "rus");

    game();

    return 0;
}

// основная функция игры
int game()
{
    // создание файла
    std::string filename = "Field.txt";

    // запись элементов в файл (наполнение файла размерами поля и координатами)
    writeToFile(filename);

    // открытие файла
    std::ifstream file(filename);

    // проверка на открытие файла
    if (!file.is_open())
    {
        std::cout << "Ошибка открытия файла для чтения!";
        return -1;
    }

    // объявление и получение из файла количества строк и столбцов поля
    int rows, columns;
    file >> rows >> columns;

    // создание поля (содержит текущее значение элементов)
    char** current_field = createArray(rows, columns);
    // создание поля, которое будет содержать клетки после изменения
    char** after_generation_field = createArray(rows, columns);

    // создание поля с "мертвыми" элементами для обоих полей
    createField(current_field, rows, columns);
    createField(after_generation_field, rows, columns);

    // наполнение поля "живыми" элементами обоих полей
    fillFieldWithLivingElements(filename, current_field);
    fillFieldWithLivingElements(filename, after_generation_field);

    printResult(current_field, after_generation_field, rows, columns);

    // закрытие файла
    file.close();

    // освобождение памяти (текущее поле)
    deleteArray(current_field, rows);
    deleteArray(after_generation_field, rows);

    return 0;
}

// печать итоговых результатов
void printResult(char** field, char** after_generation_field, const int& rows, const int& columns)
{
    // проверка процесса "жизни" (проверка изменения поля)
    bool life_process_check = true;
    // количетсво живых элементов
    int count_living;
    // количетсво новых поколений
    int generation = 1;
    // строка с выводом результата почему развитие остановилось
    std::string result;

    // пока поле меняется и количество "живых" элементов != 0
    while (life_process_check)
    {
        // проверка количества "живых" элементов на поле
        life_process_check = isNumberOfLiving(field, rows, columns, count_living, result);

        // пока есть живые элементы
        if (life_process_check)
        {
            // очистка консоли перед новым выводом
            clearConsole();

            // печать поля и выводов по количеству генерация, "живых" элементов и,
            // в случае остановки изменений, выводов почему развитие остановилось
            printArray(field, rows, columns);
            std::cout << "Generation: " << generation << ". Alive cells: " << count_living << "\n";
            std::cout << "\n";

            // увеличения числа генерации
            generation++;

            // приостановка вывода
            std::this_thread::sleep_for(std::chrono::milliseconds(500));

            // генерация нового поля с измененными клетками
            deathAndNewLifeCell(field, after_generation_field, rows, columns);

            // проверка поменялось ли поле между новой генерацией и старой
            life_process_check = isLifeStagnated(field, after_generation_field, rows, columns, result);

            // завершение работы генераций, т.к. поле после новой генерации не изменилось
            if (!life_process_check)
                break;

            // старое поле обновляется до послесгенерированного
            copyField(field, after_generation_field, rows, columns);
        }
    }

    // очистка консоли перед новым выводом
    clearConsole();

    // печать последнего итогового поля
    printArray(field, rows, columns);
    std::cout << "Generation: " << generation << " Alive cells: " << count_living << "\n";
    std::cout << result;
}

// очистка экрана перед каждым новым выводом
void clearConsole()
{
#ifdef _WIN32
    std::system("cls");
#else
    std::system("clear");
#endif
}