#include "Excel.h"

int main() {
	/*
	std::string s = CSVToString("read_csv_test.csv");
	// �Ʒ��� ���� ASCII �� ���ڵ��� ANSI �� �ƴ��� Ȯ���� �� �ִ�.
	for (int i = 0; i < 128; i++) {
		if (s[0] == i){
			printf("%d�� %c�̴�.", i, i);
		}
	}
	*/

	//readUTF8_locale("read_csv_test.csv");
	//readUTF8_fopen("read_csv_test.csv");
	CExcel cExcel;
	cExcel.SetCSV_utf8("read_csv_tet.csv");
	std::vector<std::vector<std::string>> excel = cExcel.GetExcel();
	std::cout << excel[0][2] << std::endl;
	return 0;
}