#pragma warning(disable:4996)

#include <winsock2.h>
#pragma comment(lib, "ws2_32")

#include <iostream> 
using std::cout;
using std::cin;
using std::endl;
using std::reference_wrapper;
using std::ref;

#include <cstdlib>
using std::atoi;

#include <thread>
using std::thread;

#define PACKET_SIZE 1024

WSADATA wsaData;
SOCKET sktClient;

void recvData(SOCKET _socket)
{
	char szBuffer[PACKET_SIZE];
	while (1)
	{
		ZeroMemory(szBuffer, PACKET_SIZE);
		if(recv(_socket, szBuffer, PACKET_SIZE, 0) == -1)
		{
			if (errno == EINTR)
				cout << "[CLIENT] : (recvData) signal�� �߻��Ͽ� ���� ���մϴ�." << endl;
			else
				cout << "[CLIENT] : (recvData) SERVER ���� ������ ������ϴ�." << endl;
			
			closesocket(sktClient);
			WSACleanup();
			return;
		}

		cout << szBuffer << endl;
		cout << ">> ";
	}
	return;
}

void openSocket(char IP[], int PORT)
{
	int nError;
	nError = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (nError != 0)
	{
		cout << "[CLIENT] : WSAStartup() ���� : " << WSAGetLastError() << " �� �߻��߽��ϴ�." << endl;
		return;
	}

	SOCKADDR_IN sktaddrClient = {};
	sktaddrClient.sin_family = AF_INET;
	sktaddrClient.sin_port = htons(PORT);
	sktaddrClient.sin_addr.s_addr = inet_addr(IP);

	sktClient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sktClient == INVALID_SOCKET)
	{
		cout << "[CLIENT] : socket() ���� : " << WSAGetLastError() << " �� �߻��߽��ϴ�." << endl;

		closesocket(sktClient);
		WSACleanup();
		return;
	}
	
	if (connect(sktClient, reinterpret_cast<const sockaddr*>(&sktaddrClient), sizeof(sktaddrClient)) == SOCKET_ERROR)
	{
		cout << "[CLIENT] : connect() ���� : " << WSAGetLastError() << " �� �߻��߽��ϴ�." << endl;

		closesocket(sktClient);
		WSACleanup();
		return;
	}

	char szBuffer[PACKET_SIZE];
	ZeroMemory(szBuffer, sizeof(szBuffer));

	if (recv(sktClient, szBuffer, PACKET_SIZE, 0) == -1)
	{
		if (errno == EINTR)
			cout << "[CLIENT] : (recvData) signal�� �߻��Ͽ� ���� ���մϴ�." << endl;
		else
			cout << "[CLIENT] : (recvData) " << strerror(errno) << endl;

		closesocket(sktClient);
		WSACleanup();
		return;
	}

	int nClientNum = atoi(szBuffer);

	sprintf(szBuffer, "[%d] %s::%d", nClientNum, inet_ntoa(sktaddrClient.sin_addr), ntohs(sktaddrClient.sin_port));

	int nBufferLength;
	wchar_t wstrBuffer[PACKET_SIZE * 2];
	ZeroMemory(wstrBuffer, sizeof(wstrBuffer));

	nBufferLength = static_cast<int>(strlen(szBuffer)) + 1;
	mbstowcs(wstrBuffer, szBuffer, nBufferLength);

	SetConsoleTitle(wstrBuffer);

	thread(recvData, ref(sktClient)).detach();

	while (1)
	{
		if (WSAGetLastError())
		{
			cout << "[CLIENT] : �� �� ���� ���� : " << WSAGetLastError() << " �� �߻��߽��ϴ�." << endl;
			break;
		}

		cout << ">> ";

		cin >> szBuffer;

		send(sktClient, szBuffer, strlen(szBuffer), 0);
	}

	closesocket(sktClient);
	WSACleanup();
	return;
}

int main()
{
	char IP[100];
	int PORT;

	cout << "[CLIENT] : ������ ��ȣ�� �Է����ּ���." << endl;
	cout << ">> ";

	cin >> IP;

	cout << "[CLIENT] : ��Ʈ��ȣ�� �Է����ּ���." << endl;
	cout << ">> ";

	cin >> PORT;

	openSocket(IP, PORT);
	return 0;
}