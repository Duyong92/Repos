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
	WORD mVersionRequested;
	WSADATA wsaData;
	SOCKADDR_IN serverAddress, clientAddress;

	int nError;
	int nBytesSent;
	char szBuffer[1024];

	mVersionRequested = MAKEWORD(1, 1);
	nError = WSAStartup(mVersionRequested, &wsaData);

	if (nError != 0)
	{
		cout << "[Server][" << currentTime() << "] :  WSAStartup error: " << WSAGetLastError() << endl;
		WSACleanup();
		return false;
	}

	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons(SERVER_PORT);
	serverAddress.sin_addr.s_addr = inet_addr(IPADDRESS);

	SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (serverSocket == INVALID_SOCKET)
	{
		cout << "[Server][" << currentTime() << "] : Socket error: " << WSAGetLastError() << endl;
		WSACleanup();
		return false;
	}

	int _bind = bind(serverSocket, reinterpret_cast<const sockaddr*>(&serverAddress), sizeof(serverAddress));

	if (_bind == SOCKET_ERROR)
	{
		cout << "[Server][" << currentTime() << "] : Binding error: " << WSAGetLastError() << endl;
		WSACleanup();
		return false;
	}

	cout << "Waiting for client..." << endl;

	listen(serverSocket, 5);

	int nClientSize = sizeof(clientAddress);

	SOCKET clientSocket = accept(serverSocket, reinterpret_cast<sockaddr*>(&clientAddress), &nClientSize);

	int nNumber = 0;
	int nCount = 0;

	while (true)
	{
		nCount = recv(clientSocket, szBuffer, 50, 0);

		if (nCount <= 0)
		{
			cout << "[Server][" << currentTime() << "] : Got nothing" << endl;
			break;
		}

		szBuffer[nCount] = 0;

		if (!strcmp(szBuffer, "HELLO"))
		{
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
			cout << "[Server][" << currentTime() << "] : Sending " << strNumber << " to client" << endl;

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