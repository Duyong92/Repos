#include "Client.h"

bool LoadClient()
{
	WORD wVersionRequested;
	WSADATA wsaData;
	SOCKADDR_IN target;
	SOCKET s;

	int err;
	int bytesSent;
	char buf[50];
	char sendBuf[50];

	wVersionRequested = MAKEWORD(1, 1);
	err = WSAStartup(wVersionRequested, &wsaData);

	if (err != 0)
	{
		cout << "WSAStartup error: " << WSAGetLastError() << endl;
		WSACleanup();
		return false;
	}

	target.sin_family = AF_INET;
	target.sin_port = htons(SERVER_PORT);
	// 본문에는 IPAddress 소문자 표기 되어 있어 대문자로 바꾸어줬다.
	target.sin_addr.s_addr = inet_addr(IPADDRESS);

	s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (s == INVALID_SOCKET)
	{
		cout << "Socket error: " << WSAGetLastError() << endl;
		WSACleanup();
		return false;
	}

	if (connect(s, reinterpret_cast<const sockaddr*>(&target), sizeof(target)) == SOCKET_ERROR)
	{
		cout << "Connect error: " << WSAGetLastError() << endl;
		cout << "try after when the server is loaded" << endl;
		WSACleanup();
		return false;
	}

	cout << "Sending HELLO..." << endl;

	bytesSent = send(s, "HELLO", strlen("HELLO"), 0);

	int n;
	//std::string sRand;
	//int iRand;

	while (true)
	{
		try
		{
			n = recv(s, buf, 50, 0);

			if (n <= 0)
			{
				cout << "Got nothing" << endl;
				break;
			}

			buf[n] = 0;

			cout << "(Client)Received: " << buf << endl;

			/*sRand = buf;
			iRand = stoi(sRand);

			std::this_thread::sleep_for(std::chrono::seconds(1));*/

			cout << "(Client)Type in the message : " << endl;
			std::cin >> buf;

			//cout << "(Client)Sending \"" << ++iRand << "\"" << " to server" << endl;
			cout << "(Client)Sending " << buf << " to server" << endl;
			
			/*sRand = std::to_string(iRand);
			bytesSent = send(s, sRand.c_str(), sRand.length(), 0);*/
			
			char* arr_ptr = &buf[0];
			bytesSent = send(s, buf, strlen(arr_ptr), 0);
		}
		catch (const std::invalid_argument& ex)	// invalid_argument?
		{
			std::cerr << "Invalid argument while converting string to number" << endl;
			std::cerr << "Error: " << ex.what() << endl;
			break;
		}
		catch (const std::out_of_range& ex)
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