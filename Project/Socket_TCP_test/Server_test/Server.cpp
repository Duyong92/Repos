#include "Server.h"

int MakeRandomNumber() 
{
	random_device rd;
	mt19937 rng(rd());
	uniform_int_distribution<> ud(1, 1024);

	cout << "[Server] :  Random number made" << endl;

	return ud(rng);
}

int main(void) 
{
	WORD mVersionRequested;	// unsigned short 2 byte ũ��� CPU �� �ѹ��� ó���� �� �ִ� ������ ũ�� �����̴�.
	WSADATA wsaData;	// Winsock �� �ʱ�ȭ�� �� WSADATA ���� ������ �ּҸ� �����ϱ� ���� �ʱ�ȭ�Ѵ�.
	SOCKADDR_IN serverAddress, clientAddress;	// SOCKADDR_IN ����ü�� �ʱ�ȭ�Ѵ�.

	int nError;
	int nBytesSent;
	char szBuffer[1024];

	mVersionRequested = MAKEWORD(1, 1);	// ����� Winsock �������� 2 ������ 0x0202, MAKEWORD(2, 2)�� �ʱ�ȭ�Ѵ�.
	/* int WSAStartup(WORD wVersionRequested, LPWSADATA lpWSAData)
	wVersionRequired :  ���ø����̼� ����� �� �ִ� Winsock API �����̴�.
	lpWSAData : WSADATA Ÿ���� ����ü�� ���� �������̴�. */
	nError = WSAStartup(mVersionRequested, &wsaData);

	cout << "[Server][" << currentTime() << "] : Server started" << endl;
	cout << "iMaxSockets :" << wsaData.iMaxSockets << endl;
	cout << "iMaxUdpDg :" << wsaData.iMaxUdpDg << endl;
	cout << "szDescription :" << wsaData.szDescription << endl;
	cout << "szSystemStatus :" << wsaData.szSystemStatus << endl;
	cout << "wHighVersion :" << wsaData.wHighVersion << endl;
	cout << "wVersion :"  << wsaData.wVersion << endl;

	if (nError != 0)
	{
		cout << "[Server][" << currentTime() << "] :  WSAStartup error: " << WSAGetLastError() << endl;
		WSACleanup();
		return false;
	}

	serverAddress.sin_family = AF_INET;	// IPv4 �ּ�ü���̸� �׻� AF_INET �� ����Ѵ�.
	serverAddress.sin_port = htons(SERVER_PORT);	// 16 ��Ʈ short Ÿ�� ��Ʈ��ȣ�̴�.
	/* 32 ��Ʈ ���� Ÿ�� ����ü�̴�.
	Window ���������� s_addr S_un.S_addr �� �����Ͽ� s_addr �� ����Ͽ��� ���� ����.*/
	serverAddress.sin_addr.s_addr = inet_addr(IPADDRESS);	

	/* int socket(int af, int type, int protocol)
	af : ��Ʈ��ũ �ּ�ü��� IPv4 �� ����� ��� AF_INET �� ����Ѵ�.
	type : ���� Ÿ������ TCP �� ����� ��� SOCK_STREAM(1) �� ����Ѵ�.
	protocol : �������� Ÿ������ TCP �� ����� ��� IPPROTO_TCP(6) �� ����Ѵ�. 
	���� �� 
		���� �� : file descriptor
		���� �� : -1 */
	SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (serverSocket == INVALID_SOCKET)	// INVALID_SOCKET : (SOCKET)(~0)
	{
		cout << "[Server][" << currentTime() << "] : Socket error: " << WSAGetLastError() << endl;
		WSACleanup();
		return false;
	}

	/* int bind(SOCKET s, const struct sockaddr FAR * name, int namelen)
	s : �ּҸ� �Ҵ��ϰ��� �ϴ� ������ file descriptor �̴�.
	name : �Ҵ��ϰ��� �ϴ� �ּ� ������ ���ϰ� �ִ� sockaddr ����ü ������ ������ ���� ���̴�.
	addrlen :  ���ڷ� ���޵� �ּ� ���� ����ü�� �����̴�.
	���� ��
		���� �� : 0
		���� �� : -1 */
	int _bind = bind(serverSocket, reinterpret_cast<const sockaddr*>(&serverAddress), sizeof(serverAddress));

	if (_bind == SOCKET_ERROR)	// SOCKET : -1
	{
		cout << "[Server][" << currentTime() << "] : Binding error: " << WSAGetLastError() << endl;
		WSACleanup();
		return false;
	}

	cout << "Waiting for client..." << endl;

	/* int listen(SOCKET s, int backlog)
	s : Ŭ���̾�Ʈ�κ��� ���� ��û�� �޾Ƶ��̱� ���� ���� file descriptor �̴�.
	backlog : ���� ��û ��� ť�� ũ�⿡ ���� �����̴�.
	���� �� 
		���� �� : 0
		���� �� : -1 */
	listen(serverSocket, 5);

	int nClientSize = sizeof(clientAddress);
	/* int accept(SOCKET s, struct sockaddr FAR * addr, int FAR * addrlen)
	s : ���� ������ file descriptor �̴�.
	addr : ���� ��û�� ���� �� Ŭ���̾�Ʈ�� �ּ� ������ ������ ������ �������̴�.
	addrlen : addr �� ����Ű�� ����ü�� ũ�⸦ �����ϰ� �ִ� ������ �������̴�.
	���� ��
		���� �� : ���� ���� file descriptor
		���� �� : -1 */
	SOCKET clientSocket = accept(serverSocket, reinterpret_cast<sockaddr*>(&clientAddress), &nClientSize);

	int nNumber = 0;
	int nCount = 0;

	while (true)
	{
		/* int recv(SOCKET s, char FAR * buf, int len, int flags)
		s : connect(2), accept(2) �� ����� socket descriptor �̴�.
		buf : �����͸� �����Ͽ� ������ �����̴�.
		len : ���� ������ ũ���̴�.
		flags : ���� ������ ���� �Ǵ� �д� ����� ���� option �̴�.
			MSG_OOB : out of band(��޵�����) �����͸� �д´�.
			MSG_PEEK : receive queue�� �����͸� queue���� �������� �ʰ� Ȯ���ϱ� ���� �������� �����Ѵ�.
			MSG_WAITALL : �������� �����Ͱ� buffer�� �� ������ ����Ѵ�.
		���� ��
			������ : ������ ������ ���̸� ��ȯ�Ѵ�.
			���� �� : -1 �� ���� ������ errno �� ����ȴ�. */
		nCount = recv(clientSocket, szBuffer, 50, 0);

		if (nCount <= 0)
		{
			cout << "[Server][" << currentTime() << "][ Errno : " << errno << " ] : Got nothing "<< endl;
			break;
		}

		szBuffer[nCount] = 0;

		if (!strcmp(szBuffer, "Client"))
		{
			cout << "[Server][" << currentTime() << "] : Client connected" << endl;
			nNumber = MakeRandomNumber();
			string strNumber = to_string(nNumber);

			cout << "[Server][" << currentTime() << "] : Sending random number \"" << nNumber << "\" to the client." << endl;
			nBytesSent = send(clientSocket, strNumber.c_str(), strNumber.length(), 0);
			
			continue;
		}

		string strRecievedNumber(szBuffer);

		try
		{
			cout << "[Server][" << currentTime() << "] : " << "\"" << strRecievedNumber << "\" recieved" << endl;
			sleep_for(seconds(3));

			nNumber = MakeRandomNumber();
			auto strNumber = to_string(nNumber);
			cout << "[Server][" << currentTime() << "] : Sending random number \"" << nNumber << "\" to the client." << endl;

			nBytesSent = send(clientSocket, strNumber.c_str(), strNumber.length(), 0);
		}
		catch (const invalid_argument& ex)
		{
			std::cerr << "Invalid argument while converting string to number" << endl;
			std::cerr << "Error: " << ex.what() << endl;
			break;
		}
		catch (const out_of_range& ex)
		{
			std::cerr << "Invalid argument while converting string to number" << endl;
			std::cerr << "Error: " << ex.what() << endl;
			break;
		}		
	}

	closesocket(serverSocket);
	WSACleanup();

	return 0;
} 