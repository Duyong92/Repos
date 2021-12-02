#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <istream>
#include "csv_read_row.h"

// csv 파일 안에 있는 데이터를 읽어서 vector에 저장한다.
// istream file : 파일 변수
// char delimiter : 구분자 char
std::vector<std::string> csv_read_row(std::istream& file, char delimiter);

int main()
{
	// ifstream file("파일명 or 경로")
	std::ifstream file("C:\\Users\\User\\source\\Downloads\\211012_XFA1_001_1.csv");

	// bad() 함수가 실패하는 경우이다.
	if (file.fail())
	{
		return (std::cout << "해당 경로에 위치하는 파일이 존재하지 않습니다." << std::endl) && 0;
	}

    // eof, bad, fail 함수가 거짓의 참을 반환할 때까지 반복된다.
    while (file.good()) 
    {
        std::vector<std::string> row = csv_read_row(file, ',');

        if (!row[0].find("#")) //만약 csv 파일 안에 # 문자가 있을경우
        {
            continue; //그냥 건너 뛰어라
        }
        else //#문자가 없을 경우
        {
            for (int i = 0, leng = row.size() - 2; i < leng; i++)
                std::cout << "[" << row[i] << "]" << "\t"; //알맞게 출력
        }
        std::cout << std::endl;
    }
    file.close(); //파일 입출력 완료 후 닫아준다.
    return 0;
}