#include <string>
#include <iostream>

// �������� ���� ����� (�������� (�����������) � ������) �� ������������
// � ���� ��� ����������, �� "�����" ������� � ���������
bool isLifeStagnated(char** current_gen, char** next_gen, const int& rows, const int& columns, std::string& result)
{
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < columns; j++)
		{
			// �������� �� ���������� ������ � ������� � ������ �����
			if (next_gen[i][j] != current_gen[i][j])
				return true;
			else
				// ������� ������ ����� ������ (��� ���������) � �������
				result = "The world has stagnated. Game Over.\n";
		}

	return false;
}

// �������� (�������) ���������� "�����" ��������� �� ����
bool isNumberOfLiving(char** field, const int& rows, const int& columns, int& count_living, std::string& result)
{
	int count = 0;

	// ������� "�����" ������ �� ����
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < columns; j++)
			if (field[i][j] == '*')
				count++;

	// �� ������ ���������� ���������� ����� ������ ��� ������ ����������
	count_living = count;

	// ���� "�����" ������ �� ���� ����, �� ������������ false � ���� ������
	// ��������� ��������������� � ����� �������� �� ������ (��� ���������)
	// ������������ ������ � �������
	if (count == 0)
	{
		// �� ������ � ���������� ���������� �������� �����
		result = "There are no \"living\" cells left on the field.\n";
		return false;
	}

	return true;
}