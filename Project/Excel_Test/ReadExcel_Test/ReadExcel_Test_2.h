#pragma once
#ifdef _WIN32
#include <Windows.h>
#endif

class Excel_CSV
{
private:
	// 2���� ������ �� ũ���̴�.
	unsigned int _unMaxColumn;
	// 2���� ������ �� ũ���̴�.
	unsigned int _unMaxRow;
	// �� ������ ��
	unsigned int _unSensors;
	// ���� �迭 ���͸� ���� 2 ���� �����̴�.
	std::vector<std::vector<char*>> vvpszData;
public:
	Excel_CSV();
	std::vector<std::vector<char*>> GetCSV();
	unsigned int GetMaxRow();
	unsigned int GetMaxColumn();
};

char* to_CharPoint(std::string _sBuffer)
{
	// ���� ���� ���� �迭�̴�.
	// ���Ƿ� 1024 ����Ʈ�� �����ϰ� 0 ���� �ʱ�ȭ �Ѵ�
	char* pszCell = new char[1024];

	// �ӽ� ���ڿ��� �޸𸮰� �ʱ�ȭ�� ���� �迭�� �޸𸮺��� Ŭ ��
	if (_sBuffer.size() > 1024)
		// �ӽ� ���ڿ� ũ�⸸ŭ ���� �迭 ũ�⵵ �÷��ش�.
		pszCell = new char[_sBuffer.size()];

	// �ӽ÷� ������ ���ڿ��� char* ���·� �����Ѵ�.
	strcpy(pszCell, _sBuffer.c_str());

	return pszCell;
}

// fopen �� ���ڷ� char* �� �Է��ϰ� �Ű������� ���� ���̴�.
Excel_CSV::Excel_CSV()
{
#ifdef _WIN32
	SetConsoleOutputCP(CP_UTF8);
#endif
	// fopen �� ���ڷ� char* �� filename �� �Է� �ް� �� ���̴�.
	// �б� ���� �׽�Ʈ���� ������ ����.
	FILE* fp = fopen("../read_csv_test.csv", "rt");

	// �ƽ�Ű�ڵ带 ���� �����̴�.
	char _szASCII;

	// �ӽ÷� ���ڿ��� ������ �����̴�.
	std::string _sBuffer = "";

	// ���� �迭�� ���� �����̴�.
	std::vector<char*> vpszData;

	// �ִ� ����� �ʱ�ȭ ���ش�.
	_unMaxColumn = 0;
	_unMaxRow = 0;

	// ������ �������� ���� ��� ��ó���� �Ѵ�.
	if (fp == NULL)
	{
		perror("�ش��ϴ� ������ �������� �ʽ��ϴ�.");
	}
	else
	{
		// ���Ϸκ��� �� ���ھ� �ƽ�Ű�ڵ�� �޴´�.
		do
		{
			_szASCII = static_cast<char>(fgetc(fp));
			// ���� ����(�ƽ�Ű�ڵ� 10)�� ���
			if (_szASCII == 10)
			{
				// ���� �迭�� ���� �迭 ���Ϳ� �ִ´�.
				vpszData.push_back(to_CharPoint(_sBuffer));

				// ���� �迭 ���͸� 2 ���� ���Ϳ� �ִ´�.
				vvpszData.push_back(vpszData);

				// �ִ� �� ũ�⸦ ���Ŵ�.
				if (_unMaxColumn < vpszData.size())
					_unMaxColumn = vpszData.size();

				// ���� �迭 ���͸� �ʱ�ȭ�Ѵ�.
				vpszData.clear();

				// �ӽ� ���ڿ��� �ʱ�ȭ�Ѵ�.
				_sBuffer = "";

				// �ִ� �� ũ�⸦ �����Ѵ�.
				_unMaxRow++;
			}
			// ��ǥ(�ƽ�Ű�ڵ� 44)�� ���
			else if (_szASCII == 44)
			{
				// ���� �迭�� ���� �迭 ���Ϳ� �ִ´�.
				vpszData.push_back(to_CharPoint(_sBuffer));

				// �ӽ� ���ڿ��� �ʱ�ȭ�Ѵ�.
				_sBuffer = "";
			}
			else
			{ 
				_sBuffer += _szASCII;
			}
		} while (_szASCII != EOF);
		// ���� �ݱ� ���� �� EOF �� ��ȯ�ȴ�.
		fclose(fp);
	}
};

std::vector<std::vector<char*>> Excel_CSV::GetCSV() { return vvpszData; };
unsigned int Excel_CSV::GetMaxRow() { return _unMaxRow; };
unsigned int Excel_CSV::GetMaxColumn() { return _unMaxColumn; };