#pragma warning(disable:4996)
#include <iostream>
#include <fstream>
#include <cstdio>	// 프로그래밍 언어 : ANSI
#include <vector>
#include <string>
#include "ReadExcel_Test.h"

int main() 
{
	std::vector<std::vector<char*>> Excel;
	Excel = ReadExcel_Test();
	std::cout << Excel[3][0] << std::endl;
	return 0;
}