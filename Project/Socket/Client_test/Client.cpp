#include "Client.h"

int main(void)
{
	WORD wVersionRequested;
	WSADATA wsaData;
	SOCKADDR_IN target;
	SOCKET clientSocket;

	int nError;
	int nBytesSent;
	char szBuffer[50];

	wVersionRequested = MAKEWORD(1, 1);
	nError = WSAStartup(wVersionRequested, &wsaData);

	if (nError != 0)
	{
		cout << "[Client][" << currentTime() << "] : WSAStartup error: " << WSAGetLastError() << endl;
		WSACleanup();
		return false;
	}

	target.sin_family = AF_INET;
	target.sin_port = htons(SERVER_PORT);
	target.sin_addr.s_addr = inet_addr(IPADDRESS);

	clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (clientSocket == INVALID_SOCKET)
	{
		cout << "[Client][" << currentTime() << "] : Socket error: " << WSAGetLastError() << endl;
		WSACleanup();
		return false;
	}

	if (connect(clientSocket, reinterpret_cast<const sockaddr*>(&target), sizeof(target)) == SOCKET_ERROR)
	{
		cout << "[Client][" << currentTime() << "] : Connect error: " << WSAGetLastError() << endl;
		cout << "try after when the server is loaded" << endl;
		WSACleanup();
		return false;
	}

	cout << "Sending HELLO..." << endl;

	nBytesSent = send(clientSocket, "HELLO", strlen("HELLO"), 0);

	int nCounet;
	string strNumber;
	int nNumber;

	while (true)
	{
		try
		{
			nCounet = recv(clientSocket, szBuffer, 50, 0);

			if (nCounet <= 0)
			{
				cout << "Got nothing" << endl;
				break;
			}

			szBuffer[nCounet] = 0;

			cout << "[Client][" << currentTime() << "] : \"" << szBuffer << "\" received" << endl;

			strNumber = szBuffer;
			nNumber = stoi(strNumber);

			std::this_thread::sleep_for(std::chrono::seconds(3));

			cout << "[Client][" << currentTime() << "] : Sending \"" << ++nNumber << "\"" << " to server" << endl;

			strNumber = std::to_string(nNumber);
			nBytesSent = send(clientSocket, strNumber.c_str(), strNumber.length(), 0);

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

	closesocket(clientSocket);
	WSACleanup();

	return 0;
}