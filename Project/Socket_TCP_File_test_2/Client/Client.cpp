#pragma warning(disable:4996)
#include <Winsock2.h>
#include <WS2tcpip.h>
#pragma comment(lib, "Ws2_32.lib")

// W2A _lpw 식별하는 USES_CONVERSION을 쓰기 위해
#include <atlbase.h>

#include <iostream>
#include <string>

#define IPADDRESS "127.0.0.1"
#define PORT 27015
#define BUFFER_SIZE 80
#define HEADER_SIZE

using namespace std;

int getFileSize(FILE* _file) {
	int nFileSize;
	fseek(_file, 0, SEEK_END);
	nFileSize = ftell(_file);
	rewind(_file);
	
	return nFileSize;
}

void main() {
	WSADATA wsaData;
	SOCKET sktClient;
	SOCKADDR_IN sktaddrClient;

	char pszBuffer[BUFFER_SIZE];
	char pszPath[256];

	int nLength;
	int nCount = 0;

	// C28193
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	sktClient = socket(AF_INET, SOCK_STREAM, 0);
	
	ZeroMemory(&sktaddrClient, sizeof(sktaddrClient));
	inet_pton(AF_INET, IPADDRESS, &sktaddrClient.sin_addr);
	sktaddrClient.sin_family = AF_INET;
	sktaddrClient.sin_family = htons(PORT);
	
	connect(sktClient, (const sockaddr*)&sktaddrClient, sizeof(sktaddrClient));

	WIN32_FIND_DATA fileData;
	HANDLE handle;
	handle = FindFirstFile(_T("C:\\Users\\User\\Desktop\\"), &fileData);
	
	

	do {
		if (!(fileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
			USES_CONVERSION;
			sprintf(pszPath, "C:\\Users\\User\\Desktop\\%s", W2A(fileData.cFileName));

			FILE* file;
			file = fopen(pszPath, "rb");

			pszBuffer[0] = '*';
			unsigned char uszNameSize = (unsigned char)strlen(W2A(fileData.cFileName));
			memcpy(&pszBuffer[1], &uszNameSize, 1);
			int nFileSize = getFileSize(file);
			memcpy(&pszBuffer[2], W2A(fileData.cFileName), uszNameSize);
			memcpy(&pszBuffer[2 + uszNameSize], &nFileSize, sizeof(int));
			nLength = 2 + uszNameSize + sizeof(int);
			send(sktClient, pszBuffer, nLength, 0);

			while ((nLength = fread(pszBuffer, 1, BUFFER_SIZE, file)) != NULL) {
				send(sktClient, pszBuffer, nLength, 0);
			}
		}
	} while (FindNextFile(handle, &fileData) != 0);

	FindClose(handle);
	closesocket(sktClient);
}