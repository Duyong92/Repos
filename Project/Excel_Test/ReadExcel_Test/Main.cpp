#pragma warning(disable:4996)
#include <iostream>
#include <fstream>
#include <cstdio>	// ���α׷��� ��� : ANSI
#include <vector>
#include <string>
#include "ReadExcel_Test.h"

int main() 
{
	std::cout << "���Ƿ� '../read_csv_test.csv' ��ο� �ִ� csv�� �аڽ��ϴ�." << std::endl;
	Excel_CSV Excel;
	std::vector<std::vector<char*>> csv = Excel.GetCSV();
	// �ð��� ����� ���� �ʿ��� �ӽ� �������̴�.
	unsigned int second;
	unsigned int minute;
	unsigned int hour;

	std::cout << "���������� csv�� �о����ϴ�." << std::endl << std::endl;
	std::cout << "�ʿ��� �������� �ð��븦 ��/��/�� ������� �Է����ּ���." << std::endl;
	std::cin >> hour;
	std::cin >> minute;
	std::cin >> second;
	second += (minute * 60 + hour * 3600);
	for(int i = 1; i < Excel.GetMaxColumn(); i++)
	{
		std::cout << csv[0][i] << " ";
	}
	std::cout << std::endl;
	for (int j = 2; j < Excel.GetMaxRow(); j++)
	{
		if (std::stoi(csv[j][0]) == second)
		{
			for (int i = 1; i < Excel.GetMaxColumn(); i++)
			{
				std::cout << csv[j][i] << " ";
			}
			std::cout << std::endl;
		}
	}

	return 0;
}