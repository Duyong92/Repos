#include "Client.h"

using namespace std;

void Client_1() 
{
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa)) 
	{
		cout << "WSA error";
		WSACleanup();
		return;
	}

	SOCKET skt;
	skt = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (skt == INVALID_SOCKET) 
	{
		cout << "socket error";
		closesocket(skt);
		WSACleanup();
		return;
	}

	SOCKADDR_IN addr = {};
	addr.sin_family = AF_INET;
	addr.sin_port = htons(4444);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");

	while (connect(skt, (SOCKADDR*)&addr, sizeof(addr)));

	while (1) // 반복문 추가
	{ 
		cout << "CLIENT_1" << endl;
	}

	closesocket(skt);
	WSACleanup();
}