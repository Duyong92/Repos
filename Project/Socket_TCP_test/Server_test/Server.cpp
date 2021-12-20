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
	WORD mVersionRequested;	// unsigned short 2 byte 크기로 CPU 가 한번에 처리할 수 있는 데이터 크기 단위이다.
	WSADATA wsaData;	// Winsock 을 초기화할 때 WSADATA 형식 변수의 주소를 전달하기 위해 초기화한다.
	SOCKADDR_IN serverAddress, clientAddress;	// SOCKADDR_IN 구조체를 초기화한다.

	int nError;
	int nBytesSent;
	char szBuffer[1024];

	mVersionRequested = MAKEWORD(1, 1);	// 사용할 Winsock 버전으로 2 버전은 0x0202, MAKEWORD(2, 2)로 초기화한다.
	/* int WSAStartup(WORD wVersionRequested, LPWSADATA lpWSAData)
	wVersionRequired :  애플리케이션 사용할 수 있는 Winsock API 버젼이다.
	lpWSAData : WSADATA 타입의 구조체에 대한 포인터이다. */
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

	serverAddress.sin_family = AF_INET;	// IPv4 주소체계이며 항상 AF_INET 을 사용한다.
	serverAddress.sin_port = htons(SERVER_PORT);	// 16 비트 short 타입 포트번호이다.
	/* 32 비트 정수 타입 구조체이다.
	Window 내부적으로 s_addr S_un.S_addr 을 정의하여 s_addr 을 사용하여도 지장 없다.*/
	serverAddress.sin_addr.s_addr = inet_addr(IPADDRESS);	

	/* int socket(int af, int type, int protocol)
	af : 네트워크 주소체계로 IPv4 를 사용할 경우 AF_INET 을 사용한다.
	type : 소켓 타입으로 TCP 를 사용할 경우 SOCK_STREAM(1) 을 사용한다.
	protocol : 프로토콜 타입으로 TCP 를 사용할 경우 IPPROTO_TCP(6) 을 사용한다. 
	리턴 값 
		성공 시 : file descriptor
		실패 시 : -1 */
	SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (serverSocket == INVALID_SOCKET)	// INVALID_SOCKET : (SOCKET)(~0)
	{
		cout << "[Server][" << currentTime() << "] : Socket error: " << WSAGetLastError() << endl;
		WSACleanup();
		return false;
	}

	/* int bind(SOCKET s, const struct sockaddr FAR * name, int namelen)
	s : 주소를 할당하고자 하는 소켓의 file descriptor 이다.
	name : 할당하고자 하는 주소 정보를 지니고 있는 sockaddr 구조체 변수의 포인터 인자 값이다.
	addrlen :  인자로 전달된 주소 정보 구조체의 길이이다.
	리턴 값
		성공 시 : 0
		실패 시 : -1 */
	int _bind = bind(serverSocket, reinterpret_cast<const sockaddr*>(&serverAddress), sizeof(serverAddress));

	if (_bind == SOCKET_ERROR)	// SOCKET : -1
	{
		cout << "[Server][" << currentTime() << "] : Binding error: " << WSAGetLastError() << endl;
		WSACleanup();
		return false;
	}

	cout << "Waiting for client..." << endl;

	/* int listen(SOCKET s, int backlog)
	s : 클라이언트로부터 연결 요청을 받아들이기 위한 소켓 file descriptor 이다.
	backlog : 연결 요청 대기 큐의 크기에 대한 설정이다.
	리턴 값 
		성공 시 : 0
		실패 시 : -1 */
	listen(serverSocket, 5);

	int nClientSize = sizeof(clientAddress);
	/* int accept(SOCKET s, struct sockaddr FAR * addr, int FAR * addrlen)
	s : 서버 소켓의 file descriptor 이다.
	addr : 연결 요청을 수락 할 클라이언트의 주소 정보를 저장할 변수의 포인터이다.
	addrlen : addr 이 가리키는 구조체의 크기를 저장하고 있는 변수의 포인터이다.
	리턴 값
		성공 시 : 새로 생긴 file descriptor
		실패 시 : -1 */
	SOCKET clientSocket = accept(serverSocket, reinterpret_cast<sockaddr*>(&clientAddress), &nClientSize);

	int nNumber = 0;
	int nCount = 0;

	while (true)
	{
		/* int recv(SOCKET s, char FAR * buf, int len, int flags)
		s : connect(2), accept(2) 로 연결된 socket descriptor 이다.
		buf : 데이터를 수신하여 저장할 버퍼이다.
		len : 읽을 데이터 크기이다.
		flags : 읽을 데이터 유형 또는 읽는 방법에 대한 option 이다.
			MSG_OOB : out of band(긴급데이터) 데이터를 읽는다.
			MSG_PEEK : receive queue의 데이터를 queue에서 제거하지 않고 확인하기 위한 목적으로 설정한다.
			MSG_WAITALL : 읽으려는 데이터가 buffer에 찰 때까지 대기한다.
		리턴 값
			성공시 : 수신한 데이터 길이를 반환한다.
			실패 시 : -1 롸 상세한 내용은 errno 에 저장된다. */
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