#pragma warning(disable:4996)
#include <iostream>
#include <fstream>
#include <cstdio>	// ���α׷��� ��� : ANSI
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