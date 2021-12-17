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
	// �������� IPAddress �ҹ��� ǥ�� �Ǿ� �־� �빮�ڷ� �ٲپ����.
	servAddr.sin_addr.s_addr = inet_addr(IPADDRESS);

	SOCKET s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);	// IPPROTO_TCP?

	if (s == INVALID_SOCKET) 
	{
		cout << "Socket error: " << WSAGetLastError() << endl;
		WSACleanup();
		return false;
	}
	
	// reinterpret_cast: Ÿ�� ĳ��Ʈ ������ 
	// ���������� Ÿ���� ���������� �ʾ����� bind() �Լ� ���ڸ� ���� �����Ͽ� �����ߴ�.
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

	// ���������� reinterpret_cast Ÿ���� ���������� �ʾ����� accept() �Լ� ���ڸ� ���� �����Ͽ� �����ߴ�.
	// C28193: 's2'(��)�� ������ ���� �˻��ؾ� �մϴ�
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
			// �޴� ���� ������ auto = std::basic_string<char, std::char_traits<char>, std::allocator<char>>
			auto sRand = std::to_string(iRand);	

			cout << "(Server)Sending random number " << iRand << " to the client." << endl;
			bytesSent = send(s2, sRand.c_str(), sRand.length(), 0);

			continue;
		}

		std::string sNum(buf);

		try
		{
			//iRand = stoi(sNum);	// buf �� ���� �ȵǴ� ���ΰ�?
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
	// Ŭ���� ���ø� "std::uniform_int_distribution"�� ���� �μ� ����� �����ϴ�.
	// ������ '<>' ������ �ٽ� �� �־���.
	uniform_int_distribution<> ud(1, 1024);

	return ud(rng);
}