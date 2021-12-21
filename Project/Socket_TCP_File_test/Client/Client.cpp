#include <WinSock2.h>
#include <WS2tcpip.h>
#include <atlbase.h>
#pragma comment(lib,"Ws2_32.lib")

#include <iostream>
using std::cout;
using std::endl;
using std::cin;

#include <string>
using std::string;
using std::wstring;

#define IPADDRESS "127.0.0.1"
#define BUFFER_SIZE 80
#define HEADER_SIZE

int getFileSize(FILE* _file)
{
	int nRet;
	/*int fseek(FILE* stream, long int offset, int origin);
	stream : �۾��� ������ ��Ʈ���� FILE ��ü�� ����Ű�� �������̴�.
	offset : origin ���κ��� �󸶳� ������ ���� ������ ���� ���� ���̴�.
	origin : offset �� �������� ��ġ�̸�, ��ũ�� ����� �̿��Ѵ�.
	���� �� 
		���� �� : 0
		���� �� : 0�� �ƴ� �� */
	fseek(_file, 0, SEEK_END);
	/* long int ftell(FILE *stream);
	   off_t ftello(FILE *stream);
	stream : �۾��� ������ ��Ʈ���� FILE ��ü�� ����Ű�� �������̴�.
	���� ��
		���� �� : file ��ġ�� �����´�.
		���� �� : -1,
	*/
	nRet = ftell(_file);
	rewind(_file);

	return nRet;
}

wstring s2ws(const string& _string)
{
	int nLength;
	int strLength = (int)_string.length() + 1;
	nLength = MultiByteToWideChar(CP_ACP, 0, _string.c_str(), strLength, 0, 0);
	wchar_t* pwszBuffer = new wchar_t[nLength];
	MultiByteToWideChar(CP_ACP, 0, _string.c_str(), strLength, pwszBuffer, nLength);
	wstring wString(pwszBuffer);
	delete[] pwszBuffer;
	return wString;
}

void main()
{
	SOCKET sktClient;
	SOCKADDR_IN sktaddrClient;
	WSADATA wsaData;
	
	char pszBuffer[BUFFER_SIZE];
	char pszPath[256];
	
	const int PORT = 27015;
	
	int nLength;
	int nError;
	int nCount = 0;

	string strFileDirectory;

	// WSADATA �� ���� �Ҵ�
	nError = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (nError != 0)
	{
		cout << "[CLIENT] : WSAStartup() ���� : " << WSAGetLastError() << " �� �߻��߽��ϴ�." << endl;
		return;
	}

	// ���� ����
	sktClient = socket(AF_INET, SOCK_STREAM, 0);	// IPPROTO_TCP �� ����?
	memset(&sktaddrClient, 0, sizeof(sktaddrClient));
	//ZeroMemory(&sktaddrClient, sizeof(sktaddrClient));
	if (sktClient == INVALID_SOCKET)
	{
		cout << "[CLIENT] : socket() ���� : " << WSAGetLastError() << " �� �߻��߽��ϴ�." << endl;

		closesocket(sktClient);
		WSACleanup();
		return;
	}
	
	// ���� �ּ� �Ҵ�
	inet_pton(AF_INET, IPADDRESS, &sktaddrClient.sin_addr);
	sktaddrClient.sin_port = htons(PORT);
	sktaddrClient.sin_family = AF_INET;

	// ���� �ּҿ� ���� ����
	if (connect(sktClient, reinterpret_cast<const sockaddr*>(&sktaddrClient), sizeof(sktaddrClient)) == SOCKET_ERROR)
	{
		cout << "[CLIENT] : connect() ���� : " << WSAGetLastError() << " �� �߻��߽��ϴ�." << endl;

		closesocket(sktClient);
		WSACleanup();
		return;
	}

	// ���� ��ġ ã��
	WIN32_FIND_DATA FindFileData;
	HANDLE hFind;

	cout << "[CLIENT] : ã���÷��� ������ ���丮�� �Է����ּ���." << endl;
	cout << ">> ";
	cin >> strFileDirectory;

	/*HANDLE FindFirstFile(LPCTSTR lpFileName, LPWIN32_FIND_DATA lpFindFileData)
	lpFileName : ã������ ������ �������̴�.
	lpFindFileData : �������� ������ �����Ѵ�. */
	hFind = FindFirstFile(s2ws(strFileDirectory).c_str(), &FindFileData);
	if (hFind == INVALID_HANDLE_VALUE)
	{
		cout << "[CLIENT] : FindFirstFile() ���� : " << GetLastError() << endl;
		return;
	}

	do 
	{
		if (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)	// �Ӽ��� ���丮�� ��� ó��
			cout << "[CLIENT] : ������ �Ӽ��� ���丮�Դϴ�. FILENAME : " << FindFileData.cFileName << endl;
		else
		{
			USES_CONVERSION;

			cout << "[CLIENT] : FILENAME : " << FindFileData.cFileName << endl;

			sprintf(pszPath, strFileDirectory.c_str(), W2A(FindFileData.cFileName));

			FILE* file;
			file = fopen(pszPath, "rb");

			pszBuffer[0] = '*';	// �޽��� ���� ����
			unsigned char uszNameSize = (unsigned char)strlen(W2A(FindFileData.cFileName));	// ���ϸ� ������
			memcpy(&pszBuffer[1], &uszNameSize, 1);
			int nFileSize = getFileSize(file);	// ���� ������ ������
			memcpy(&pszBuffer[2], W2A(FindFileData.cFileName), uszNameSize);
			memcpy(&pszBuffer[2+uszNameSize], &nFileSize, sizeof(int));
			nLength = 2 + uszNameSize + sizeof(int);	// ��ü �޽��� ������
			nError = send(sktClient, pszBuffer, nLength, 0);

			if (nError == SOCKET_ERROR)
			{
				cout << "[CLIENT] : send() ���� : " << WSAGetLastError() << endl;
				closesocket(sktClient);
				WSACleanup();
				return;
			}

			while ((nLength = fread(pszBuffer, 1, BUFFER_SIZE, file)) != NULL)	// ���Ͽ��� BUFFER_SIZE ��ŭ read �õ�, nLegnth ������ ������ ���� byte ��
			{
				nError = send(sktClient, pszBuffer, nLength, 0);	// nLength ũ�� ��ŭ ����

				if (nError == SOCKET_ERROR)
				{
					cout << "[CLIENT] : send() ���� : " << WSAGetLastError() << endl;
					closesocket(sktClient);
					WSACleanup();
					return;
				}
			}
		}
	} while (FindNextFile(hFind, &FindFileData) != 0);	// ������ ��� ã�´�.

	FindClose(hFind);
	closesocket(sktClient);
}