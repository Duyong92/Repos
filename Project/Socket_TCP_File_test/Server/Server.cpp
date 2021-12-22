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
		cout << "[SERVER] : WSAStartup() 오류 : " << WSAGetLastError() << " 가 발생했습니다." << endl;
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
	hostname : 호스트 이름 혹은 주소 문자열(주소 문자열은 IPv4의 점으로 구분하는 10진 주소 문자열)이다.
	service :  서비스 이름 혹은 10진수로 표현한 포트 번호 문자열이다.
	hints : getaddrinfo 함수에게 말 그대로 힌트를 준다. 디폴트는 NULL 이다.
	ressult : DNS 서버로부터 받은 네트워크 주소 정보를 돌려주는 output 매개변수이다. */
	nError = getaddrinfo(NULL, PORT, &hints, &result);
	if (nError != 0)
	{
		cout << "[SERVER] : getaddrinfo() 오류 : " << WSAGetLastError() << " 가 발생했습니다." << endl;
		WSACleanup();
		return 1;
	}

	sktServer = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
	if (sktServer == INVALID_SOCKET)
	{
		cout << "[SERVER] : socket() 오류 : " << WSAGetLastError() << " 가 발생했습니다." << endl;

		closesocket(sktServer);
		WSACleanup();
		return 1;
	}

	nError = bind(sktServer, result->ai_addr, (int)result->ai_addrlen);
	if(nError == SOCKET_ERROR)
	{
		cout << "[SERVER] : bind() 오류 : " << WSAGetLastError() << " 가 발생했습니다." << endl;

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
                if (pszBuffer[cnt] == '*')    // 메시지 시작 문자
                {
                    cnt++;
                    memcpy(&nFileNameSize, &pszBuffer[cnt], 1);     // 파일명 크기
                    cnt++;
                    memcpy(pszFileName, &pszBuffer[cnt], nFileNameSize);       // 파일 데이터 크기
                    pszFileName[nFileNameSize] = 0;
                    cnt += nFileNameSize;

                    printf("pszFileName:%s\n", pszFileName);

                    memcpy(&nSize, &pszBuffer[cnt], sizeof(int)); // 실제 파일 데이터
                    cnt += sizeof(int);
                    if (cnt >= nLength)
                        break;
                }

                // 메시지 안의 파일 데이터가 헤더에 들어있는 크기보다 작거나 같은 경우
                // 같을 경우에는 메시지 끝까지 파일 데이터가 들어있고 더 이상 전송되지 않음
                // 작을 경우에는 데이터 다음에 *부터 다시 시작하는 데이터가 들어있는 것임, while(cnt < nLength)문을 돌며 계속 처리.
                if (nLength - cnt <= nSize)
                {
                    FILE* fp;
                    fp = fopen(pszFileName, "ab");
                    fwrite(&pszBuffer[cnt], 1, nLength - cnt, fp);
                    fclose(fp);

                    nSize -= (nLength - cnt);
                    cnt += (nLength - cnt);
                }

                // 메시지 안의 파일 데이터가 헤더에 들어있는 크기보다 클 경우
                // 전달받은 buffer를 모두 썼기 때문에 while(1)문을 돌며 메시지를 다시 recv하여 계속 처리함. 
                // 파일에 이미 쓴 크기를 nSize(파일크기)에서 빼서, 앞으로 쓸 크기만큼만 계산해 놓는다. 
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