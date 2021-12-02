#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <istream>
#include "csv_read_row_test.h"

using namespace std;

vector<string> csv_read_row_test(istream& file, char delimiter);

int main()
{
	ifstream file("read_csv_test.csv");

	if (file.fail())
	{
		return (cout << "�ش� ��ο� ��ġ�ϴ� ������ �������� �ʽ��ϴ�." << endl) && 0;
	}
	while (file.good())
	{
		vector<string> row = csv_read_row_test(file, ',');

		if (!row[0].find('#'))
		{
			continue;
		}
		else
		{
			for (int i = 0, leng = row.size() - 2; i < leng; i++)
				cout << row[i] << "\t";
			cout << endl;
		}
		file.close();
		return 0;
	}
}