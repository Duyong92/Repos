#pragma once
#ifdef _WIN32
#include <Windows.h>
#endif

class Excel_CSV
{
private:
	// 2차원 벡터의 열 크기이다.
	unsigned int _unMaxColumn;
	// 2차원 벡터의 행 크기이다.
	unsigned int _unMaxRow;
	// 총 센서의 수
	unsigned int _unSensors;
	// 문자 배열 벡터를 받을 2 차원 벡터이다.
	std::vector<std::vector<char*>> vvpszData;
public:
	Excel_CSV();
	std::vector<std::vector<char*>> GetCSV();
	unsigned int GetMaxRow();
	unsigned int GetMaxColumn();
};

char* to_CharPoint(std::string _sBuffer)
{
	// 셀을 받을 문자 배열이다.
	// 임의로 1024 바이트로 설정하고 0 으로 초기화 한다
	char* pszCell = new char[1024];

	// 임시 문자열에 메모리가 초기화된 문자 배열의 메모리보다 클 때
	if (_sBuffer.size() > 1024)
		// 임시 문자열 크기만큼 문자 배열 크기도 늘려준다.
		pszCell = new char[_sBuffer.size()];

	// 임시로 저장한 문자열을 char* 형태로 저장한다.
	strcpy(pszCell, _sBuffer.c_str());

	return pszCell;
}

// fopen 의 인자로 char* 을 입력하게 매개변수를 받을 것이다.
Excel_CSV::Excel_CSV()
{
#ifdef _WIN32
	SetConsoleOutputCP(CP_UTF8);
#endif
	// fopen 의 인자로 char* 의 filename 을 입력 받게 할 것이다.
	// 읽기 전용 테스트모드로 파일을 연다.
	FILE* fp = fopen("../read_csv_test.csv", "rt");

	// 아스키코드를 받을 변수이다.
	char _szASCII;

	// 임시로 문자열을 보관할 변수이다.
	std::string _sBuffer = "";

	// 문자 배열을 받을 벡터이다.
	std::vector<char*> vpszData;

	// 최대 행렬을 초기화 해준다.
	_unMaxColumn = 0;
	_unMaxRow = 0;

	// 파일이 존재하지 않을 경우 전처리를 한다.
	if (fp == NULL)
	{
		perror("해당하는 파일이 존재하지 않습니다.");
	}
	else
	{
		// 파일로부터 한 글자씩 아스키코드로 받는다.
		do
		{
			_szASCII = static_cast<char>(fgetc(fp));
			// 개행 문자(아스키코드 10)일 경우
			if (_szASCII == 10)
			{
				// 문자 배열을 문자 배열 벡터에 넣는다.
				vpszData.push_back(to_CharPoint(_sBuffer));

				// 문자 배열 벡터를 2 차원 벡터에 넣는다.
				vvpszData.push_back(vpszData);

				// 최대 행 크기를 갱신다.
				if (_unMaxColumn < vpszData.size())
					_unMaxColumn = vpszData.size();

				// 문자 배열 벡터를 초기화한다.
				vpszData.clear();

				// 임시 문자열을 초기화한다.
				_sBuffer = "";

				// 최대 열 크기를 갱신한다.
				_unMaxRow++;
			}
			// 쉼표(아스키코드 44)일 경우
			else if (_szASCII == 44)
			{
				// 문자 배열을 문자 배열 벡터에 넣는다.
				vpszData.push_back(to_CharPoint(_sBuffer));

				// 임시 문자열을 초기화한다.
				_sBuffer = "";
			}
			else
			{ 
				_sBuffer += _szASCII;
			}
		} while (_szASCII != EOF);
		// 파일 닫기 실패 시 EOF 가 반환된다.
		fclose(fp);
	}
};

std::vector<std::vector<char*>> Excel_CSV::GetCSV() { return vvpszData; };
unsigned int Excel_CSV::GetMaxRow() { return _unMaxRow; };
unsigned int Excel_CSV::GetMaxColumn() { return _unMaxColumn; };