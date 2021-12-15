#include "Excel.h"

int main() {
	std::string s = CSVToString("read_csv_test.csv");
	for(int i = 0; i < 100; i++)
		std::cout << i << "¹øÂ° : " << s[i] << std::endl;
	if (s[0] == 0xEF || s[0] == 0xFF || s[0] == 0xBB || s[0] == 0xBF)
		std::cout << "YES" << std::endl;

	return 0;
}