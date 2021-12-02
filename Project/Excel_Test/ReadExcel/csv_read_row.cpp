#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <istream>
#include "csv_read_row.h"

// csv ���� �ȿ� �ִ� �����͸� �о vector�� �����Ѵ�.
// istream file : ���� ����
// char delimiter : ������ char
std::vector<std::string> csv_read_row(std::istream& file, char delimiter);

int main()
{
	// ifstream file("���ϸ� or ���")
	std::ifstream file("C:\\Users\\User\\source\\Downloads\\211012_XFA1_001_1.csv");

	// bad() �Լ��� �����ϴ� ����̴�.
	if (file.fail())
	{
		return (std::cout << "�ش� ��ο� ��ġ�ϴ� ������ �������� �ʽ��ϴ�." << std::endl) && 0;
	}

    // eof, bad, fail �Լ��� ������ ���� ��ȯ�� ������ �ݺ��ȴ�.
    while (file.good()) 
    {
        std::vector<std::string> row = csv_read_row(file, ',');

        if (!row[0].find("#")) //���� csv ���� �ȿ� # ���ڰ� �������
        {
            continue; //�׳� �ǳ� �پ��
        }
        else //#���ڰ� ���� ���
        {
            for (int i = 0, leng = row.size() - 2; i < leng; i++)
                std::cout << "[" << row[i] << "]" << "\t"; //�˸°� ���
        }
        std::cout << std::endl;
    }
    file.close(); //���� ����� �Ϸ� �� �ݾ��ش�.
    return 0;
}