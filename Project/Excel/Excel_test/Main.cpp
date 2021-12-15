#include "Excel.h"

int main() {
	/*
	std::string s = CSVToString("read_csv_test.csv");
	// 아래와 같이 ASCII 로 인코딩이 ANSI 가 아님을 확인할 수 있다.
	for (int i = 0; i < 128; i++) {
		if (s[0] == i){
			printf("%d는 %c이다.", i, i);
		}
	}
	*/

	//readUTF8_locale("read_csv_test.csv");
	//readUTF8_fopen("read_csv_test.csv");
	CExcel cExcel;
	cExcel.SetCSV("211012_XFA1_001_1.csv");
	std::vector<std::vector<std::string>> excel = cExcel.GetExcel();
	std::cout << excel[0][2] << std::endl;
	return 0;
}