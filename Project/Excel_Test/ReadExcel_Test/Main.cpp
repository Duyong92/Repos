#pragma warning(disable:4996)
#include <iostream>
#include <fstream>
#include <cstdio>	// ���α׷��� ��� : ANSI
#include <vector>
#include <string>
// #include "ReadExcel_Test.h"
#include "ReadExcel_Test_2.h"

int main() 
{
	std::cout << "���Ƿ� '../read_csv_test.csv' ��ο� �ִ� csv�� �аڽ��ϴ�." << std::endl;
	Excel_CSV Excel;
	std::vector<std::vector<char*>> csv = Excel.GetCSV();
	std::cout << "���������� csv�� �о����ϴ�." << std::endl << std::endl;

	// �ð��� ����� ���� �ʿ��� �ӽ� �������̴�.
	std::string time = "";
	std::string sBuffer = "";
	char val = 'N';

	while (val) {
		std::cout << "�ʿ��� �������� �ð��븦 ��/��/�� ������� �Է����ּ���." << std::endl;
		std::cin >> sBuffer;
		time += sBuffer += ":";
		std::cin >> sBuffer;
		time += sBuffer += ":";
		std::cin >> sBuffer;
		time += sBuffer;
		std::cout << "�Է��Ͻ� �ð��� " << time << "�� �½��ϱ� ? [Y / N]" << std::endl;
		std::cin >> val;
		if (val == 'Y' || val == 'y') 
			break;
	}
	
	for(int i = 1; i < Excel.GetMaxColumn(); i++)
	{
		std::cout << csv[0][i] << " ";
	}
	std::cout << std::endl;
	for (int j = 2; j < Excel.GetMaxRow(); j++)
	{
		if (csv[j][0] == time)
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