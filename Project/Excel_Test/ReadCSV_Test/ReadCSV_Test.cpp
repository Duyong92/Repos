#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int main() {
	string str_buf;
	fstream fs;
	int count = 0;

	fs.open("../read_csv_test.csv", ios::in);
	while (!fs.eof()) {
		++count;
		getline(fs, str_buf, ',');
		cout << "sdf" << str_buf << endl;
		
	}
	fs.close();

	return 0;
}