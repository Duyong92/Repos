#include "Excel.h"

int main() {
	/*std::string s = CSVToString("read_csv_test.csv");
	for(int i = 0; i < 100; i++)
		std::cout << i << "¹øÂ° : " << s[i] << std::endl;
	if (s[0] == 0xEF || s[0] == 0xFF || s[0] == 0xBB || s[0] == 0xBF)
		std::cout << "YES" << std::endl;*/

	/*
	// SetCSV(), SetCSV_utf8() example
	CExcel cExcel;
	cExcel.SetCSV("211012_XFA1_001_1.csv");
	std::cout << cExcel.GetExcel()[3][0] << std::endl;
	CExcel cExcel_utf8;
	cExcel_utf8.SetCSV_utf8("read_csv_test.csv");
	std::cout << cExcel_utf8.GetExcel()[3][0] << std::endl;
	*/

	std::cout << ReadText_utf8("read_csv_test.csv") << std::endl;
	//std::cout << ReadText("211012_XFA1_001_1.csv") << std::endl;

	return 0;
}