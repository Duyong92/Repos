#pragma warning(disable:4996)
#undef UNICODE
#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include <Winsock2.h>
#include <Ws2tcpip.h>
#pragma comment(lib,"Ws2_32.lib")

#include <stdlib.h>
#include <stdio.h>

#include <iostream>
using std::cout;
using std::endl;
using std::cin;

#include <string>
using std::string;

#define BUFFER_LENGTH 4096
#define PORT "27015"

int main(void)
{
	WSADATA wsaData;
	SOCKET sktServer = INVALID_SOCKET;
	SOCKET sktClient = INVALID_SOCKET;
	
	struct addrinfo* result = NULL;
	struct addrinfo hints;

	char pszBuffer[BUFFER_LENGTH];
	char pszFileName[256];

	int nError;
	
	// Initialize Winsock
	nError = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (nError != 0)
	{
		cout << "[SERVER] : WSAStartup() ���� : " << WSAGetLastError() << " �� �߻��߽��ϴ�." << endl;
		return 1;
	}

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;

	// Resolve the erver address and port
	/*int getaddrinfo(PCSTR pNodeName, PCSTR pServiceName, const ADDRINFOA * pHints, PADDRINFOA * ppResult)
	* int getaddrinfo(const char *hostname, const char *service, const struct addrinfo *hints, struct addrinfo **result);
	hostname : ȣ��Ʈ �̸� Ȥ�� �ּ� ���ڿ�(�ּ� ���ڿ��� IPv4�� ������ �����ϴ� 10�� �ּ� ���ڿ�)�̴�.
	service :  ���� �̸� Ȥ�� 10������ ǥ���� ��Ʈ ��ȣ ���ڿ��̴�.
	hints : getaddrinfo �Լ����� �� �״�� ��Ʈ�� �ش�. ����Ʈ�� NULL �̴�.
	ressult : DNS �����κ��� ���� ��Ʈ��ũ �ּ� ������ �����ִ� output �Ű������̴�. */
	nError = getaddrinfo(NULL, PORT, &hints, &result);
	if (nError != 0)
	{
		cout << "[SERVER] : getaddrinfo() ���� : " << WSAGetLastError() << " �� �߻��߽��ϴ�." << endl;
		WSACleanup();
		return 1;
	}

	sktServer = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
	if (sktServer == INVALID_SOCKET)
	{
		cout << "[SERVER] : socket() ���� : " << WSAGetLastError() << " �� �߻��߽��ϴ�." << endl;

		closesocket(sktServer);
		WSACleanup();
		return 1;
	}

	nError = bind(sktServer, result->ai_addr, (int)result->ai_addrlen);
	if(nError == SOCKET_ERROR)
	{
		cout << "[SERVER] : bind() ���� : " << WSAGetLastError() << " �� �߻��߽��ϴ�." << endl;

		closesocket(sktServer);
		WSACleanup();
		return 1;
	}

	freeaddrinfo(result);

    nError = listen(sktServer, SOMAXCONN);
    if (nError == SOCKET_ERROR)
    {
        printf("listen failed with error: %d\n", WSAGetLastError());

        closesocket(sktServer);
        WSACleanup();
        return 1;
    }

    // Accept a client socket
    while (1)
    {
        sktClient = accept(sktServer, NULL, NULL);
        if (sktClient == INVALID_SOCKET)
        {
            printf("accept failed with error: %d\n", WSAGetLastError());

            closesocket(sktServer);
            WSACleanup();
            return 1;
        }

        int nLength;
        int cnt = 0;
        int nSize = 0;
        int nFileNameSize = 0;
        int nDataCnt = 0;

        while (1)
        {
            if ((nLength = recv(sktClient, pszBuffer, sizeof(pszBuffer), 0)) < 0)
                return -1;
            if (nLength == 0)
                break;

            cnt = 0;
            while (cnt < nLength)
            {
                if (pszBuffer[cnt] == '*')    // �޽��� ���� ����
                {
                    cnt++;
                    memcpy(&nFileNameSize, &pszBuffer[cnt], 1);     // ���ϸ� ũ��
                    cnt++;
                    memcpy(pszFileName, &pszBuffer[cnt], nFileNameSize);       // ���� ������ ũ��
                    pszFileName[nFileNameSize] = 0;
                    cnt += nFileNameSize;

                    printf("pszFileName:%s\n", pszFileName);

                    memcpy(&nSize, &pszBuffer[cnt], sizeof(int)); // ���� ���� ������
                    cnt += sizeof(int);
                    if (cnt >= nLength)
                        break;
                }

                // �޽��� ���� ���� �����Ͱ� ����� ����ִ� ũ�⺸�� �۰ų� ���� ���
                // ���� ��쿡�� �޽��� ������ ���� �����Ͱ� ����ְ� �� �̻� ���۵��� ����
                // ���� ��쿡�� ������ ������ *���� �ٽ� �����ϴ� �����Ͱ� ����ִ� ����, while(cnt < nLength)���� ���� ��� ó��.
                if (nLength - cnt <= nSize)
                {
                    FILE* fp;
                    fp = fopen(pszFileName, "ab");
                    fwrite(&pszBuffer[cnt], 1, nLength - cnt, fp);
                    fclose(fp);

                    nSize -= (nLength - cnt);
                    cnt += (nLength - cnt);
                }

                // �޽��� ���� ���� �����Ͱ� ����� ����ִ� ũ�⺸�� Ŭ ���
                // ���޹��� buffer�� ��� ��� ������ while(1)���� ���� �޽����� �ٽ� recv�Ͽ� ��� ó����. 
                // ���Ͽ� �̹� �� ũ�⸦ nSize(����ũ��)���� ����, ������ �� ũ�⸸ŭ�� ����� ���´�. 
                else
                {
                    FILE* fp;
                    fp = fopen(pszFileName, "ab");
                    fwrite(&pszBuffer[cnt], 1, nSize, fp);
                    fclose(fp);

                    cnt += nSize;
                }
            }
        }

        closesocket(sktClient);
    }

    // No longer need server socket
    closesocket(sktServer);

    // shutdown the connection since we're done
    nError = shutdown(sktClient, SD_SEND);
    if (nError == SOCKET_ERROR)
    {
        printf("shutdown failed with error: %d\n", WSAGetLastError());
        closesocket(sktClient);
        WSACleanup();
        return 1;
    }

    // cleanup
    closesocket(sktClient);
    WSACleanup();
    return 0;
}