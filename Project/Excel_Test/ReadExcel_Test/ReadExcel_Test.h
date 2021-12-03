#pragma once

// ���ڿ��� ���� �迭�� �ٲ��ִ� �Լ��̴�.
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

// HH:MM:ss �ð� ǥ�� ���ڿ����� Ȯ���ϰ� �� ���� ���ڿ��� �ٲ��ִ� �Լ��̴�.
std::string DateFormat_Second(std::string _sBuffer)
{
	std::string temp_sBuffer = _sBuffer;

	// �� ������ ������ �����̴�.
	unsigned int _unSecond = 0;

	// ���ڿ��� ':' �� �ִ��� Ȯ���ϰ� �� ������ ���ڿ��� ġȯ���ش�.
	if (temp_sBuffer.find(":") < temp_sBuffer.length())
	{
		// �ð��� �ش�Ǵ� ���ڿ��� �� ������ ȯ���Ѵ�.
		_unSecond += 3600 * stoi(temp_sBuffer.substr(0, temp_sBuffer.find(":")));

		// �ð��� �ش�Ǵ� ���ڸ� ���ڿ����� �����
		temp_sBuffer.erase(0, temp_sBuffer.find(":") + 1);

		// �п� �ش�Ǵ� ���ڿ��� �� ������ ȯ���Ѵ�.
		_unSecond += 60 * stoi(temp_sBuffer.substr(0, temp_sBuffer.find(":")));

		// �п� �ش�Ǵ� ���ڸ� ���ڿ����� �����
		temp_sBuffer.erase(0, temp_sBuffer.find(":") + 1);

		// �ʿ� �ش�Ǵ� ���ڿ��� �� ������ ȯ���Ѵ�.
		_unSecond += stoi(temp_sBuffer.substr(0, temp_sBuffer.find(":")));

		// �� ������ ȯ��� ���� ���ڿ��� ��ȯ�����ش�.
		temp_sBuffer = std::to_string(_unSecond);
	}
	return temp_sBuffer;
}

// fopen �� ���ڷ� char* �� �Է��ϰ� �Ű������� ���� ���̴�.
std::vector<std::vector<char*>> ReadExcel_Test()
{
	// fopen �� ���ڷ� char* �� filename �� �Է� �ް� �� ���̴�.
	// �б� ���� �׽�Ʈ���� ������ ����.
	FILE* fp = fopen("../read_csv_test.csv", "rt");

	// �ƽ�Ű�ڵ带 ���� �����̴�.
	char _szASCII;

	// �ӽ÷� ���ڿ��� ������ �����̴�.
	std::string _sBuffer = "";

	// ���� �迭 ���͸� ���� 2 ���� �����̴�.
	std::vector<std::vector<char*>> vvpszData;

	// ���� �迭�� ���� �����̴�.
	std::vector<char*> vpszData;

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
				_sBuffer = DateFormat_Second(_sBuffer);

				// ���� �迭�� ���� �迭 ���Ϳ� �ִ´�.
				vpszData.push_back(to_CharPoint(_sBuffer));

				// ���� �迭 ���͸� 2 ���� ���Ϳ� �ִ´�.
				vvpszData.push_back(vpszData);

				// ���� �迭 ���͸� �ʱ�ȭ�Ѵ�.
				vpszData.clear();

				// �ӽ� ���ڿ��� �ʱ�ȭ�Ѵ�.
				_sBuffer = "";
			}
			// ��ǥ(�ƽ�Ű�ڵ� 44)�� ���
			else if (_szASCII == 44)
			{
				_sBuffer = DateFormat_Second(_sBuffer);

				// ���� �迭�� ���� �迭 ���Ϳ� �ִ´�.
				vpszData.push_back(to_CharPoint(_sBuffer));

				// �ӽ� ���ڿ��� �ʱ�ȭ�Ѵ�.
				_sBuffer = "";
			}
			else
				_sBuffer += _szASCII;
		} while (_szASCII != EOF);
		// ���� �ݱ� ���� �� EOF �� ��ȯ�ȴ�.
		fclose(fp);
	}
	return vvpszData;
}