#include <iostream>
#include <fstream>
#include <ctime>

// ��������� ����� �� ������������ (������ ���� (������ � �������) � ��������� ����� ������)
int getNumFromUser()
{
	int num;
	std::cin >> num;

	return num;
}

// �������� �� ������������ ����� ������
bool checkingUserData(const int& lines, const int& columns, const int& living_cells)
{
	// ������ ����� ������� (���������� ������ ����)
	int area = lines * columns;

	// �������� ���������� �����
	if (lines < 1)
	{
		std::cout << "���������� ����� �� ����� ���� ������ ��� ����� 0. ���� ������ ���� ���������!\n";
		return false;
	}
	// �������� ���������� ��������
	else if (columns < 1)
	{
		std::cout << "���������� �������� �� ����� ���� ������ ��� ����� 0. ���� ������ ���� ���������!\n";
		return false;
	}
	// �������� ���������� ����� �����
	else if ((living_cells < 0) || (living_cells > area))
	{
		std::cout << "���������� ����� ������ �� ������ ���� ������ 0 � ������ " << area << "\n";
		return false;
	}

	return true;
}

// ��������� ���������� ����� ��� ���������� ����
// � size ���������� ��� ���������� �����, ��� � ���������� �������� ����
// -1, �.�. ����������� ������ ���� = 0, ����� ������� ������ ������ ��������
int getRandomNum(const int size) { return (-1 + std::rand() % (-1 - size) + 1); }

// ������ � ���� ������� ���� �� ������������, � ����� ���������� ����� ������
// � ����������, ������������ �������������, ����� ��������� ���������
void writeToFile(const std::string& filename)
{
	// �������� �����
	std::ofstream file(filename);

	// �������� �� �������� �����
	if (!file.is_open())
	{
		std::cout << "�� ������� ������� ���� ��� ������.\n";
		return;
	}
	else
	{
		// ���������� ����� � �������� �� ������������
		std::cout << "���������� �����: ";
		int lines = getNumFromUser();
		std::cout << "���������� ��������: ";
		int columns = getNumFromUser();

		// ���������� ����� ������ �� ������������
		printf("������� ���������� ����� ������ � �������� �� 0 �� %d: ", lines * columns);
		int living_cells = getNumFromUser();

		// ���� ������ ������� ���������, �� ���� ����������� �������
		if (checkingUserData(lines, columns, living_cells))
		{
			// ������ � ���� ���������� ����� � �������� �� ������������
			file << lines << " " << columns << "\n";

			// ������ � ���� ���������� ������ ������ � ������� ����� ������
			// ���������� ������ ������������ ������������� (�������� ���������� ������)
			for (int i = 0; i < living_cells; i++)
			{
				// -1 - �.�. ������ ������� ���� ���������� � 0 � ���� �� ��������� -1, �� ��������
				// ������ ����� �������� �� ������� ���� (��������, ���� ������ ���� 10�10, �� ����������� ������ =9)
				int line_number = getRandomNum(lines - 1);
				int column_number = getRandomNum(columns - 1);

				// ���� ��� �� ��������� ������ � ����, �� � ����� ���� ������� ������
				// � ���� ��������� ������, �� ������� ������ �����������
				(i < living_cells - 1) ? file << line_number << " " << column_number << "\n" :
					file << line_number << " " << column_number;
			}
		}
	}

	// �������� �����
	file.close();
}
