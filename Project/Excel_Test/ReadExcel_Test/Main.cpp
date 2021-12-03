#pragma warning(disable:4996)
#include <iostream>
#include <fstream>
#include <cstdio>	// 프로그래밍 언어 : ANSI
#include <vector>
#include <string>
// #include "ReadExcel_Test.h"
#include "ReadExcel_Test_2.h"

int main() 
{
	std::cout << "임의로 '../read_csv_test.csv' 경로에 있는 csv를 읽겠습니다." << std::endl;
	Excel_CSV Excel;
	std::vector<std::vector<char*>> csv = Excel.GetCSV();
	std::cout << "성공적으로 csv를 읽었습니다." << std::endl << std::endl;

	// 시간대 계산을 위해 필요한 임시 변수들이다.
	std::string time = "";
	std::string sBuffer = "";
	char val = 'N';

	while (val) {
		std::cout << "필요한 데이터의 시간대를 시/분/초 순서대로 입력해주세요." << std::endl;
		std::cin >> sBuffer;
		time += sBuffer += ":";
		std::cin >> sBuffer;
		time += sBuffer += ":";
		std::cin >> sBuffer;
		time += sBuffer;
		std::cout << "입력하신 시간이 " << time << "이 맞습니까 ? [Y / N]" << std::endl;
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