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
	stream : 작업을 수행할 스트림의 FILE 객체를 가리키는 포인터이다.
	offset : origin 으로부터 얼마나 떨어진 곳에 설정할 지에 대한 값이다.
	origin : offset 이 더해지는 위치이며, 매크로 상수를 이용한다.
	리턴 값 
		성공 시 : 0
		실패 시 : 0이 아닌 값 */
	fseek(_file, 0, SEEK_END);
	/* long int ftell(FILE *stream);
	   off_t ftello(FILE *stream);
	stream : 작업을 수행할 스트림의 FILE 객체를 가리키는 포인터이다.
	리턴 값
		성공 시 : file 위치를 가져온다.
		실패 시 : -1,
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

	// WSADATA 및 버전 할당
	nError = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (nError != 0)
	{
		cout << "[CLIENT] : WSAStartup() 오류 : " << WSAGetLastError() << " 가 발생했습니다." << endl;
		return;
	}

	// 소켓 생성
	sktClient = socket(AF_INET, SOCK_STREAM, 0);	// IPPROTO_TCP 안 쓰나?
	memset(&sktaddrClient, 0, sizeof(sktaddrClient));
	//ZeroMemory(&sktaddrClient, sizeof(sktaddrClient));
	if (sktClient == INVALID_SOCKET)
	{
		cout << "[CLIENT] : socket() 오류 : " << WSAGetLastError() << " 가 발생했습니다." << endl;

		closesocket(sktClient);
		WSACleanup();
		return;
	}
	
	// 소켓 주소 할당
	inet_pton(AF_INET, IPADDRESS, &sktaddrClient.sin_addr);
	sktaddrClient.sin_port = htons(PORT);
	sktaddrClient.sin_family = AF_INET;

	// 소켓 주소에 소켓 연결
	if (connect(sktClient, reinterpret_cast<const sockaddr*>(&sktaddrClient), sizeof(sktaddrClient)) == SOCKET_ERROR)
	{
		cout << "[CLIENT] : connect() 오류 : " << WSAGetLastError() << " 가 발생했습니다." << endl;

		closesocket(sktClient);
		WSACleanup();
		return;
	}

	// 파일 위치 찾기
	WIN32_FIND_DATA FindFileData;
	HANDLE hFind;

	cout << "[CLIENT] : 찾으시려는 파일의 디렉토리를 입력해주세요." << endl;
	cout << ">> ";
	cin >> strFileDirectory;

	/*HANDLE FindFirstFile(LPCTSTR lpFileName, LPWIN32_FIND_DATA lpFindFileData)
	lpFileName : 찾으려는 파일의 포인터이다.
	lpFindFileData : 포인터의 정보를 리턴한다. */
	hFind = FindFirstFile(s2ws(strFileDirectory).c_str(), &FindFileData);
	if (hFind == INVALID_HANDLE_VALUE)
	{
		cout << "[CLIENT] : FindFirstFile() 오류 : " << GetLastError() << endl;
		return;
	}

	do 
	{
		if (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)	// 속성이 디렉토리일 경우 처리
			cout << "[CLIENT] : 파일의 속성이 디렉토리입니다. FILENAME : " << FindFileData.cFileName << endl;
		else
		{
			USES_CONVERSION;

			cout << "[CLIENT] : FILENAME : " << FindFileData.cFileName << endl;

			sprintf(pszPath, strFileDirectory.c_str(), W2A(FindFileData.cFileName));

			FILE* file;
			file = fopen(pszPath, "rb");

			pszBuffer[0] = '*';	// 메시지 시작 문자
			unsigned char uszNameSize = (unsigned char)strlen(W2A(FindFileData.cFileName));	// 파일명 사이즈
			memcpy(&pszBuffer[1], &uszNameSize, 1);
			int nFileSize = getFileSize(file);	// 파일 데이터 사이즈
			memcpy(&pszBuffer[2], W2A(FindFileData.cFileName), uszNameSize);
			memcpy(&pszBuffer[2+uszNameSize], &nFileSize, sizeof(int));
			nLength = 2 + uszNameSize + sizeof(int);	// 전체 메시지 사이즈
			nError = send(sktClient, pszBuffer, nLength, 0);

			if (nError == SOCKET_ERROR)
			{
				cout << "[CLIENT] : send() 오류 : " << WSAGetLastError() << endl;
				closesocket(sktClient);
				WSACleanup();
				return;
			}

			while ((nLength = fread(pszBuffer, 1, BUFFER_SIZE, file)) != NULL)	// 파일에서 BUFFER_SIZE 만큼 read 시도, nLegnth 변수는 실제로 읽은 byte 수
			{
				nError = send(sktClient, pszBuffer, nLength, 0);	// nLength 크기 만큼 전송

				if (nError == SOCKET_ERROR)
				{
					cout << "[CLIENT] : send() 오류 : " << WSAGetLastError() << endl;
					closesocket(sktClient);
					WSACleanup();
					return;
				}
			}
		}
	} while (FindNextFile(hFind, &FindFileData) != 0);	// 파일을 계속 찾는다.

	FindClose(hFind);
	closesocket(sktClient);
}