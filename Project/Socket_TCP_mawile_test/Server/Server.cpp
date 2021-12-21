#pragma warning(disable:4996)

#include <WinSock2.h>
#pragma comment(lib, "ws2_32")

#include <iostream>
using std::cout;
using std::cin;
using std::endl;
using std::reference_wrapper;
using std::ref;
using std::cerr;

#include <fstream>
#include <istream>

#include <cstdlib>
using std::atoi;

#include <thread>
using std::thread;

#include <string>
using std::string;
using std::to_string;
using std::getline;

#define PACKET_SIZE 1024

WSADATA wsaData;
SOCKET sktServer, *psktClient;
SOCKADDR_IN* psktaddrClient;
int* pnClientSize, MAX;

void recvData(SOCKET _socket, int _clientNum)
{
	char pszBuffer[PACKET_SIZE];
	string strClientNum = "[CLIENT";
	while (1)
	{
		ZeroMemory(pszBuffer, PACKET_SIZE);
		if (recv(_socket, pszBuffer, PACKET_SIZE, 0) == -1)
		{
			if (errno == EINTR)
				cout << "[SERVER] : (recvData) signal이 발생하여 읽지 못합니다." << endl;
			else
				cout << "[SERVER] : (recvData) " << strerror(errno) << endl;
			return;
		}

		cout << "\nClient Number " << _clientNum << " : " << pszBuffer << endl;
		cout << ">> ";

		strClientNum = strClientNum + to_string(_clientNum) + "] : " + pszBuffer;
		for (int i = 0; i < MAX; i++)
		{
			if(i != _clientNum)
				send(psktClient[i], strClientNum.c_str(), strClientNum.length(), 0);
		}
	}
	
	return;
}

void acceptClients()
{
	char pszClientNum[10];
	for (int i = 0; i < MAX; i++)
	{
		pnClientSize[i] = sizeof(psktaddrClient[i]);
		psktClient[i] = accept(sktServer, reinterpret_cast<sockaddr*>(&psktaddrClient[i]), &pnClientSize[i]);

		if (psktClient[i] == INVALID_SOCKET)
		{
			cout << "[SERVER] : accept() 오류 :  소켓 생성에 실패했습니다." << endl;

			closesocket(psktClient[i]);
			closesocket(sktServer);
			WSACleanup();
			return;
		}

		cout << "Client " << i << " 님이 입장하셨습니다." << endl;
		cout << ">> ";

		ZeroMemory(pszClientNum, sizeof(pszClientNum));

		itoa(i, pszClientNum, 10);

		send(psktClient[i], pszClientNum, strlen(pszClientNum), 0);

		thread (recvData, ref(psktClient[i]), i).detach();
	}

	return;
}

void openSocket(int _port)
{
	int nError;
	nError = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (nError != 0)
	{
		cout << "[SERVER] : WSAStartup() 오류 : " << WSAGetLastError() << " 가 발생했습니다." << endl;
		return;
	}

	SOCKADDR_IN sktaddrServer = {};
	sktaddrServer.sin_family = AF_INET;
	sktaddrServer.sin_port = htons(_port);
	sktaddrServer.sin_addr.s_addr = htonl(INADDR_ANY);

	sktServer = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sktServer == INVALID_SOCKET)
	{
		cout << "[SERVER] : socket() 오류 : " << WSAGetLastError() << " 가 발생했습니다." << endl;

		closesocket(sktServer);
		WSACleanup();
		return;
	}

	if (bind(sktServer, reinterpret_cast<sockaddr*>(&sktaddrServer), sizeof(sktaddrServer)))
	{
		cout << "[SERVER] : bind() 오류 : " << WSAGetLastError() << " 가 발생했습니다." << endl;
		
		closesocket(sktServer);
		WSACleanup();
		return;
	}

	if (listen(sktServer, SOMAXCONN))
	{
		cout << "[SERVER] : listen() 오류 : " << WSAGetLastError() << " 가 발생했습니다." << endl;

		closesocket(sktServer);
		WSACleanup();
		return;
	}

	thread(acceptClients).detach();

	//char pszMessage[PACKET_SIZE], pszSendNum[PACKET_SIZE];
	string strMessage, strSendNum;

	while (1)
	{
		printf(">> ");

		//cin >> pszMessage;
		cin.ignore();
		getline(cin, strMessage, '\n');
		cout << strMessage << endl;
		if (!strMessage.compare("exit")/*!strcmp(pszMessage, "exit")*/)
		{
			cout << "[SERVER] : 서버를 종료합니다." << endl;
			break;
		}
		strMessage = "[SERVER] >> " + strMessage;

		cout << "[SERVER] : 대상 클라이언트 번호를 입력해주세요.(모두일 경우 'all'을 입력해주세요.)" << endl;
		cout << ">> ";

		//cin >> pszSendNum;
		cin >> strSendNum;

		if (strSendNum == "all"/*!strcmp(pszSendNum, "all")*/)
		{
			for (int i = 0; i < MAX; i++)
				send(psktClient[i], strMessage.c_str()/*pszMessage*/, strMessage.length()/*strlen(pszMessage)*/ , 0);
				
		}
		else
			send(psktClient[stoi(strSendNum)],strMessage.c_str(),strMessage.length()/*psktClient[atoi(pszSendNum)], pszMessage, strlen(pszMessage)*/, 0);
	}

	for (int i = 0; i < MAX; i++)
		closesocket(psktClient[i]);
	closesocket(sktServer);
	WSACleanup();
	return;
}

int main()
{
	int PORT;

	cout << "[SERVER] : 포트번호를 입력해주세요." << endl;
	cout << ">> ";

	cin >> PORT;

	cout << "[SERVER] : 클라이언트 최대 수용 수를 설정해주세요." << endl;
	cout << ">> ";

	cin >> MAX;

	psktClient = new SOCKET[MAX];
	psktaddrClient = new SOCKADDR_IN[MAX];
	pnClientSize = new int[MAX];
	ZeroMemory(psktClient, sizeof(psktClient));
	ZeroMemory(psktaddrClient, sizeof(psktaddrClient));
	ZeroMemory(pnClientSize, sizeof(pnClientSize));

	openSocket(PORT);

	delete[] psktClient, psktaddrClient, pnClientSize;

	return 0;
}