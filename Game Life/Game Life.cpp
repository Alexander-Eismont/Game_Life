#include <chrono>  // milliseconds
#include <cstdlib> // ��� std::system("cls")
#include <fstream> // ��� ������ � �������
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
    // ��������� �������� ��������� ����� � �������� ���������� ����� ��� ��������� ���������
    std::srand(static_cast<unsigned int>(std::time(0)));

    setlocale(LC_ALL, "rus");

    game();

    return 0;
}

// �������� ������� ����
int game()
{
    // �������� �����
    std::string filename = "Field.txt";

    // ������ ��������� � ���� (���������� ����� ��������� ���� � ������������)
    writeToFile(filename);

    // �������� �����
    std::ifstream file(filename);

    // �������� �� �������� �����
    if (!file.is_open())
    {
        std::cout << "������ �������� ����� ��� ������!";
        return -1;
    }

    // ���������� � ��������� �� ����� ���������� ����� � �������� ����
    int rows, columns;
    file >> rows >> columns;

    // �������� ���� (�������� ������� �������� ���������)
    char** current_field = createArray(rows, columns);
    // �������� ����, ������� ����� ��������� ������ ����� ���������
    char** after_generation_field = createArray(rows, columns);

    // �������� ���� � "��������" ���������� ��� ����� �����
    createField(current_field, rows, columns);
    createField(after_generation_field, rows, columns);

    // ���������� ���� "������" ���������� ����� �����
    fillFieldWithLivingElements(filename, current_field);
    fillFieldWithLivingElements(filename, after_generation_field);

    printResult(current_field, after_generation_field, rows, columns);

    // �������� �����
    file.close();

    // ������������ ������ (������� ����)
    deleteArray(current_field, rows);
    deleteArray(after_generation_field, rows);

    return 0;
}

// ������ �������� �����������
void printResult(char** field, char** after_generation_field, const int& rows, const int& columns)
{
    // �������� �������� "�����" (�������� ��������� ����)
    bool life_process_check = true;
    // ���������� ����� ���������
    int count_living;
    // ���������� ����� ���������
    int generation = 1;
    // ������ � ������� ���������� ������ �������� ������������
    std::string result;

    // ���� ���� �������� � ���������� "�����" ��������� != 0
    while (life_process_check)
    {
        // �������� ���������� "�����" ��������� �� ����
        life_process_check = isNumberOfLiving(field, rows, columns, count_living, result);

        // ���� ���� ����� ��������
        if (life_process_check)
        {
            // ������� ������� ����� ����� �������
            clearConsole();

            // ������ ���� � ������� �� ���������� ���������, "�����" ��������� �,
            // � ������ ��������� ���������, ������� ������ �������� ������������
            printArray(field, rows, columns);
            std::cout << "Generation: " << generation << ". Alive cells: " << count_living << "\n";
            std::cout << "\n";

            // ���������� ����� ���������
            generation++;

            // ������������ ������
            std::this_thread::sleep_for(std::chrono::milliseconds(500));

            // ��������� ������ ���� � ����������� ��������
            deathAndNewLifeCell(field, after_generation_field, rows, columns);

            // �������� ���������� �� ���� ����� ����� ���������� � ������
            life_process_check = isLifeStagnated(field, after_generation_field, rows, columns, result);

            // ���������� ������ ���������, �.�. ���� ����� ����� ��������� �� ����������
            if (!life_process_check)
                break;

            // ������ ���� ����������� �� ���������������������
            copyField(field, after_generation_field, rows, columns);
        }
    }

    // ������� ������� ����� ����� �������
    clearConsole();

    // ������ ���������� ��������� ����
    printArray(field, rows, columns);
    std::cout << "Generation: " << generation << " Alive cells: " << count_living << "\n";
    std::cout << result;
}

// ������� ������ ����� ������ ����� �������
void clearConsole()
{
#ifdef _WIN32
    std::system("cls");
#else
    std::system("clear");
#endif
}