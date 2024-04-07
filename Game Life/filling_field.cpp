#include <iostream>
#include <fstream>

#include "array.h"

// �������� ���� ������ � "��������" ����������
void createField(char** field, const int& rows, const int& columns)
{
	// ���������� ������� "��������" ����������
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < columns; j++)
			field[i][j] = '-';
}

// ���������� ���� ������ ���������� �������� ������ �� �����
void fillFieldWithLivingElements(const std::string& filename, char** field)
{
	std::ifstream file(filename);

	// ������� ������ ���� ����� �� �����, ������������ ������� ����
	int size;
	file >> size >> size;

	// ���������� ��� ������ ������ ������ � ������� � "�����" ��������� �� �����
	int row, column;

	// ���������� ���� "������" ����������
	while (file >> row >> column)
		field[row][column] = '*';

	file.close();
}

// ������ ���������� ����� ������ ������ ������
// rows � columns �����, ����� ��������� ����� �� �������
// row � col - ���������� ������� ����� ������
int calcNumOfLivingAroundCell(char** field, const int& rows, const int& columns, int& row, int& col)
{
	int num_of_living = 0;

	// ���� ���������� ������, ���������� ������� ������ �� ������� ������
	// ��������, �������� � �������� �������� ���������� �� 1, ������������ �
	// ������� ����� �� ������� ����
	for (int i = row - 1; i <= row + 1; i++)
		for (int j = col - 1; j <= col + 1; j++)
		{
			// ���� ����� �� ������� ����, �� ���������� ��������
			if ((i < 0) || (j < 0) || (i > rows - 1) || (j > columns - 1))
				continue;

			// ������� ���������� ����� ������, ������ ������
			if (field[i][j] == '*')
				num_of_living++;
		}

	// ���� ���������� ������ ��������� ����� ������, �� ��������� �����
	// ���������� ��������� �� 1, �.�. ���������� ��������� ���������� ������
	// ������ ������
	if (field[row][col] == '*')
		num_of_living--;

	return num_of_living;
}

// ������� ������� � ���������� ����� ������ �� �������, ������ "������" ���
// "��������" ��������
void deathAndNewLifeCell(char** field, char** after_generation_field, const int& rows, const int& columns)
{
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < columns; j++)
		{
			after_generation_field[i][j] = field[i][j];

			// ������ ���������� ����� ������ ������ ����������� � ������ ������
			int count = calcNumOfLivingAroundCell(field, rows, columns, i, j);

			// ���� ������ ����� ������ ���������� ����� ������ 2 ��� ������ 3,
			// �� ����� ������ "�������"
			if (count < 2 || count > 3)
				//field[i][j] = '-';
				after_generation_field[i][j] = '-';

			// ���� ������ �� ����� � ������ ���� 3 ����� ������, �� � �������
			// ��������� ����� "�����"
			if (count == 3 && field[i][j] != '*')
				//field[i][j] = '*';
				after_generation_field[i][j] = '*';
		}
}

// ����������� � ������ �� ������ ����� ��������������� ����� ����
void copyField(char** field, char** after_generation_field, const int& rows, const int& columns)
{
	// �����������/���������� ��������� ���� ����� ��������� � ������ (����) 
	// �� ��������� (���������� ���������)
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < columns; j++)
			field[i][j] = after_generation_field[i][j];
}