#undef UNICODE
#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#pragma comment(lib, "Ws2_32.lib")	// Need to link with Ws2_32.lib
//#pragma comment(lib, "Mswsock.lib")

#include <iostream>
using std::cout;
using std::cin;
using std::endl;

#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "27015"

int main(void)
{
	WSADATA wsaData;
	int iResult;

	SOCKET ListenSocket = INVALID_SOCKET;
	SOCKET ClientSocket = INVALID_SOCKET;

	struct addrinfo* result = NULL;
	struct addrinfo hints;

	int iSendResult;

	//char recvbuf[DEFAULT_BUFLEN];
	//int recvbuflen = DEFAULT_BUFLEN;

	SYSTEMTIME sys_time;
	char sendbuf[DEFAULT_BUFLEN];

	// Initialize Winsock
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0)
	{
		cout << "WSAStartup failed with error: " << iResult << endl;
		return 1;
	}

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;

	// Resolve the server address and port
	/*int getaddrinfo(const char *hostname, const char *service, const struct addrinfo *hints, struct addrinfo **result);
	hostname : 호스트 이름 혹은 주소 문자열이다.
	service : 서비스 이름 혹은 10진수로 표현한 포트번호 문자열이다
	hints : getaddrinfo 에 대한 힌트를 준다?
	result : DNS 서버로부터 받은 네트워크 주소 정보를 돌려주는 output 매개변수이다. */
	iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);
	if (iResult != 0)
	{
		cout << "getaddrinfo failed with error: " << iResult << endl;
		WSACleanup();
		return 1;
	}

	// Create a SOCKET for connectin to server
	ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
	if (ListenSocket == INVALID_SOCKET)
	{
		cout << "socket failed with error: " << WSAGetLastError() << endl;
		freeaddrinfo(result);
		WSACleanup();
		return 1;
	}

	// Setup the TCP listening socket
	iResult = bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen);
	if (iResult == SOCKET_ERROR)
	{
		cout << "bind failed with error: " << WSAGetLastError() << endl;
		freeaddrinfo(result);
		closesocket(ListenSocket);
		WSACleanup();
		return 1;
	}

	freeaddrinfo(result);

	iResult = listen(ListenSocket, SOMAXCONN);
	if (iResult == SOCKET_ERROR)
	{
		cout << "listen failed with error: " << WSAGetLastError() << endl;
		closesocket(ListenSocket);
		WSACleanup();
		return 1;
	}

	// Accept a client socket
	while (1)
	{
		ClientSocket = accept(ListenSocket, NULL, NULL);
		if (ClientSocket == INVALID_SOCKET)
		{
			cout << "accept failed with error: " << WSAGetLastError() << endl;
			closesocket(ListenSocket);
			WSACleanup();
			return 1;
		}

		GetLocalTime(&sys_time);
		sprintf_s(sendbuf, DEFAULT_BUFLEN, "%04d/%02d/%02d %02d:%02d:%02d", sys_time.wYear,
			sys_time.wMonth, sys_time.wDay, sys_time.wHour, sys_time.wMinute, sys_time.wSecond);
		iSendResult = send(ClientSocket, sendbuf, strlen(sendbuf), 0);

		if (iSendResult == SOCKET_ERROR)
		{
			cout << "send failed with error: " << WSAGetLastError();
			closesocket(ClientSocket);
			WSACleanup();
			return 1;
		}

		closesocket(ClientSocket);
	}

	// No longer need server socket
	closesocket(ListenSocket);

	// shutdown the connection since we're done
	iResult = shutdown(ClientSocket, SD_SEND);
	if (iResult == SOCKET_ERROR)
	{
		cout << "shutdown failed with error: " << WSAGetLastError();
		closesocket(ClientSocket);
		WSACleanup();
		return 1;
	}

	// cleanup
	closesocket(ClientSocket);
	WSACleanup();
	return 0;
}