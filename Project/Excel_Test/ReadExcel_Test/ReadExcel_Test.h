#pragma once

// 문자열을 문자 배열로 바꿔주는 함수이다.
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

// HH:MM:ss 시간 표기 문자열인지 확인하고 초 단위 문자열로 바꿔주는 함수이다.
std::string DateFormat_Second(std::string _sBuffer)
{
	std::string temp_sBuffer = _sBuffer;

	// 초 단위를 저장할 변수이다.
	unsigned int _unSecond = 0;

	// 문자열에 ':' 가 있는지 확인하고 초 단위로 문자열로 치환해준다.
	if (temp_sBuffer.find(":") < temp_sBuffer.length())
	{
		// 시간에 해당되는 문자열을 초 단위로 환산한다.
		_unSecond += 3600 * stoi(temp_sBuffer.substr(0, temp_sBuffer.find(":")));

		// 시간에 해당되는 문자를 문자열에서 지운다
		temp_sBuffer.erase(0, temp_sBuffer.find(":") + 1);

		// 분에 해당되는 문자열을 초 단위로 환산한다.
		_unSecond += 60 * stoi(temp_sBuffer.substr(0, temp_sBuffer.find(":")));

		// 분에 해당되는 문자를 문자열에서 지운다
		temp_sBuffer.erase(0, temp_sBuffer.find(":") + 1);

		// 초에 해당되는 문자열을 초 단위로 환산한다.
		_unSecond += stoi(temp_sBuffer.substr(0, temp_sBuffer.find(":")));

		// 초 단위로 환산된 값을 문자열로 변환시켜준다.
		temp_sBuffer = std::to_string(_unSecond);
	}
	return temp_sBuffer;
}

// fopen 의 인자로 char* 을 입력하게 매개변수를 받을 것이다.
std::vector<std::vector<char*>> ReadExcel_Test()
{
	// fopen 의 인자로 char* 의 filename 을 입력 받게 할 것이다.
	// 읽기 전용 테스트모드로 파일을 연다.
	FILE* fp = fopen("../read_csv_test.csv", "rt");

	// 아스키코드를 받을 변수이다.
	char _szASCII;

	// 임시로 문자열을 보관할 변수이다.
	std::string _sBuffer = "";

	// 문자 배열 벡터를 받을 2 차원 벡터이다.
	std::vector<std::vector<char*>> vvpszData;

	// 문자 배열을 받을 벡터이다.
	std::vector<char*> vpszData;

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
				_sBuffer = DateFormat_Second(_sBuffer);

				// 문자 배열을 문자 배열 벡터에 넣는다.
				vpszData.push_back(to_CharPoint(_sBuffer));

				// 문자 배열 벡터를 2 차원 벡터에 넣는다.
				vvpszData.push_back(vpszData);

				// 문자 배열 벡터를 초기화한다.
				vpszData.clear();

				// 임시 문자열을 초기화한다.
				_sBuffer = "";
			}
			// 쉼표(아스키코드 44)일 경우
			else if (_szASCII == 44)
			{
				_sBuffer = DateFormat_Second(_sBuffer);

				// 문자 배열을 문자 배열 벡터에 넣는다.
				vpszData.push_back(to_CharPoint(_sBuffer));

				// 임시 문자열을 초기화한다.
				_sBuffer = "";
			}
			else
				_sBuffer += _szASCII;
		} while (_szASCII != EOF);
		// 파일 닫기 실패 시 EOF 가 반환된다.
		fclose(fp);
	}
	return vvpszData;
}