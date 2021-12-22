#pragma warning(disable:4996)
#undef UNICODE
#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include <winerror.h>
#include <Winsock2.h>
#include <WS2tcpip.h>
#pragma comment(lib, "Ws2_32.lib")

#include <stdlib.h>
#include <stdio.h>

#include <iostream>
#include <string>

#define IPADDRESS "127.0.0.1"
#define PORT "27015"
#define BUFFER_SIZE 80
#define HEADER_SIZE
#define BUFFER_LENGTH 4096

using namespace std;

int main(void) {
	WSADATA wsaData;
	SOCKET sktServer = INVALID_SOCKET, sktClient = INVALID_SOCKET;

	ADDRINFOA* result = NULL;
	ADDRINFOA hints;

	char pszBuffer[BUFFER_LENGTH];
	char pszFileName[256];

	int check;

	WSAStartup(MAKEWORD(2, 2), &wsaData);

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;

	getaddrinfo(NULL, PORT, &hints, &result);

	sktServer = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
	bind(sktServer, result->ai_addr, (int)result->ai_addrlen);
	listen(sktServer, SOMAXCONN);

	while (1) {
		sktClient = accept(sktClient, NULL, NULL);
		if (sktClient == INVALID_SOCKET) {
			closesocket(sktServer);
			WSACleanup();
			return 1;
		}

		int nLength;
		int nCount = 0;
		int nSize = 0;
		int nFileNameSize = 0;
		int nDataCount = 0;

		while (1) {
			nLength = recv(sktClient, pszBuffer, sizeof(pszBuffer), 0);

			nCount = 0;
			while (nCount < nLength)
			{
				if (pszBuffer[nCount] == '*') {
					nCount++;
					memcpy(&nFileNameSize, &pszBuffer[nCount], 1);
					
					nCount++;
					memcpy(pszFileName, &pszBuffer[nCount], nFileNameSize);
					pszFileName[nFileNameSize] = 0;
					nCount += nFileNameSize;

					memcpy(&nSize, &pszBuffer[nCount], sizeof(int));
					nCount += sizeof(int);
					
					if (nCount >= nLength)
						break;
				}
			}
			if (nLength - nCount <= nSize) {
				FILE* file;
				file = fopen(pszFileName, "ab");
				fwrite(&pszBuffer[nCount], 1, nLength - nCount, file);
				fclose(file);
				nSize -= (nLength - nCount);
				nCount += (nLength - nCount);
			}
			else {
				FILE* file;
				file = fopen(pszFileName, "ab");
				fwrite(&pszBuffer[nCount], 1, nSize, file);
				fclose(file);
				nCount += nSize;
			}
		}

		closesocket(sktClient);
	}

	closesocket(sktServer);

	shutdown(sktClient, SD_SEND);

	closesocket(sktClient);
	WSACleanup();
	return 0;
	
}