#include "Server.h"
#include "Header.h"

int makeRand();

bool LoadServer() 
{
	WORD mVersionRequested;	// WORD?
	WSADATA wsaData;	// WSADATA?
	SOCKADDR_IN servAddr, cliAddr;	// SOCKADDR_IN

	int err;
	int bytesSent;
	char buf[50];

	mVersionRequested = MAKEWORD(1, 1);	// MAKEWORD?
	err = WSAStartup(mVersionRequested, &wsaData);	// WSAStartup?

	if (err != 0)
	{
		cout << "WSAStartup error: " << WSAGetLastError() << endl;
		WSACleanup();
		return false;
	}

	servAddr.sin_family = AF_INET;	// AF_INET? , sin_family?
	servAddr.sin_port = htons(SERVER_PORT);
	// 본문에는 IPAddress 소문자 표기 되어 있어 대문자로 바꾸어줬다.
	servAddr.sin_addr.s_addr = inet_addr(IPADDRESS);

	SOCKET s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);	// IPPROTO_TCP?

	if (s == INVALID_SOCKET) 
	{
		cout << "Socket error: " << WSAGetLastError() << endl;
		WSACleanup();
		return false;
	}
	
	// reinterpret_cast: 타입 캐스트 연산자 
	// 본문에서는 타입을 지정해주지 않았지만 bind() 함수 인자를 보고 유추하여 실행했다.
	int x = bind(s, reinterpret_cast<const sockaddr*>(&servAddr), sizeof(servAddr));

	if (x == SOCKET_ERROR)
	{
		cout << "Binding error: " << WSAGetLastError() << endl;
		WSACleanup();
		return false;
	}

	// Wating -> Waiting
	cout << "Waiting for client... " << endl;

	listen(s, 5);	// listen? backlog?

	int xx = sizeof(cliAddr);

	// 본문에서는 reinterpret_cast 타입을 지정해주지 않았지만 accept() 함수 인자를 보고 유추하여 실행했다.
	// C28193: 's2'(이)가 보유한 값을 검사해야 합니다
	SOCKET s2 = accept(s, reinterpret_cast<sockaddr*>(&cliAddr), &xx);

	int iRand = 0;
	int n = 0;

	while (true)
	{
		n = recv(s2, buf, 50, 0);	// recv?

		if (n <= 0)
		{
			cout << "Got nothing" << endl;
			break;
		}

		buf[n] = 0;

		if (!strcmp(buf, "HELLO"))
		{
			iRand = makeRand();	// makeRand?
			// 받는 인자 값으로 auto = std::basic_string<char, std::char_traits<char>, std::allocator<char>>
			auto sRand = std::to_string(iRand);	

			cout << "(Server)Sending random number " << iRand << " to the client." << endl;
			bytesSent = send(s2, sRand.c_str(), sRand.length(), 0);

			continue;
		}

		std::string sNum(buf);

		try
		{
			//iRand = stoi(sNum);	// buf 를 쓰면 안되는 것인가?
			//cout << "(Server)Server got " << "\"" << iRand << "\"" << endl;
			cout << "(Server)Server got " << "\"" << sNum << "\"" << endl;

			std::this_thread::sleep_for(std::chrono::seconds(1));
			//cout << "(Server)Sending \"" << ++iRand << "\"" << " to client" << endl;
			cout << "(Server)Sending " << sNum << " to client" << endl;

			//auto sRand = std::to_string(iRand);
			//bytesSent = send(s2, sRand.c_str(), sRand.length(), 0);
			bytesSent = send(s2, buf, sNum.length(), 0);
		}
		catch (const invalid_argument& ex)	// invalid_argument?
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

	closesocket(s);
	WSACleanup();

	return 0;
}

int makeRand()
{
	random_device rd;
	mt19937 rng(rd());
	// 클래스 템플릿 "std::uniform_int_distribution"에 대한 인수 목록이 없습니다.
	// 본문에 '<>' 생략을 다시 써 주었다.
	uniform_int_distribution<> ud(1, 1024);

	return ud(rng);
}