#include <WinSock2.h>
#include <Ws2tcpip.h>

#pragma comment(lib, "Ws2_32.lib")
#define IPADDR "127.0.0.1"
#define BUFSIZE 512

#include <iostream>
using std::cout;
using std::cin;
using std::endl;

void main()
{
	const int port = 27015; // 임의 설정인 듯 하다.
	int c_socket;
	struct sockaddr_in c_addr;
	char rcvBuffer[BUFSIZE];
	int len;
	WSADATA wsaData;
	IN_ADDR inaddr;

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != NO_ERROR)
		return;

	c_socket = socket(AF_INET, SOCK_STREAM, 0);
	memset(&c_addr, 0, sizeof(c_addr));
	//c_addr.sin)addr.S_un.S_addr = inet_addr(IPADDR);
	inet_pton(AF_INET, IPADDR, &c_addr.sin_addr);
	c_addr.sin_family = AF_INET;
	c_addr.sin_port = htons(port);

	if (connect(c_socket, (struct sockaddr*)&c_addr, sizeof(c_addr)) == -1)
	{
		cout << "Cannot connect" << endl;
		closesocket(c_socket);
		return;
	}

	if ((len = recv(c_socket, rcvBuffer, sizeof(rcvBuffer), 0)) < 0)
		return;

	rcvBuffer[len] = '\0';
	cout << rcvBuffer << endl;
	closesocket(c_socket);
}