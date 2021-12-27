#pragma warning(disable:4996)
#pragma comment(lib, "Ws2_32.lib")
#include <WS2tcpip.h>
#include <string.h>
#include <time.h>
#include <iostream>

#define BUFSIZE 65536
#define PORT 9090
#define IP "127.0.0.1"

char* pszFile;
int retval;

void printe(const char* _message, int _errorType = WSAGetLastError()) {
	LPVOID lpMsgBuf;
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, _errorType,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf, 0, NULL);
	printf("[%s] %s", _message, (char*)lpMsgBuf);
	LocalFree(lpMsgBuf);
}

void WINAPI dataRecv(LPVOID _arg) {
	SOCKET skt = (SOCKET)_arg;
	SOCKADDR_IN sktaddr;
	int sktaddrSize = sizeof(sktaddr);
	getpeername(skt, (SOCKADDR*)&sktaddr, &sktaddrSize);
	do {
		retval = recv(skt, pszFile, BUFSIZE, 0);
		pszFile += retval;
		if (retval == 0)
			break;
		else if (retval == SOCKET_ERROR)
			printe("recv Error");
		break;
	} while (retval > 0);
}

int main() {
	time_t start_time, end_time;
	float gap;
	start_time = clock();	// 시작 시간 측정

	// Socket 초기화
	WSADATA wsa;
	if ((retval = WSAStartup(MAKEWORD(2, 2), &wsa)) != 0) {
		printe("WSAStartup Error", retval);
		return -1;
	}

	// Socket 생성
	SOCKET sktSize, sktData;
	sktSize = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	sktData = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	// SocketAddress 설정
	SOCKADDR_IN sktaddrSize, sktaddrData;
	int sktaddrSizeSize = sizeof(sktaddrSize);
	int sktaddrDataSize = sizeof(sktaddrData);

	ZeroMemory(&sktaddrSize, sktaddrSizeSize);
	sktaddrSize.sin_family = AF_INET;
	sktaddrSize.sin_addr.s_addr = inet_addr(IP);
	sktaddrSize.sin_port = htons(PORT);

	ZeroMemory(&sktaddrData, sktaddrDataSize);
	sktaddrData.sin_family = AF_INET;
	sktaddrData.sin_addr.s_addr = inet_addr(IP);
	sktaddrData.sin_port = htons(PORT);

	// 소켓 옵션 설정 -  수신 버퍼 크기 설정
	int retval, recvBuf = BUFSIZE;
	retval = setsockopt(sktData, SOL_SOCKET, SO_RCVBUF, (char*)&recvBuf, sizeof(recvBuf));
	printf("Recv buffer size : %d bytes\n", recvBuf);

	// Nagle 알고리즘
	int opt_val = TRUE;
	setsockopt(sktData, IPPROTO_TCP, TCP_NODELAY, (char*)opt_val, sizeof(opt_val));

	// Connet - 서버 측에 연결 요청
	unsigned int unCount = 0;
	while (unCount < 10) {
		if ((retval = connect(sktSize, (SOCKADDR*)&sktaddrSize, sktaddrSizeSize)) != SOCKET_ERROR) {
			printf("Connected");
			break;
		}
		unCount++;
		printe("Connect Error", GetLastError());
		printf("%d번째 시도 중..\n", unCount);
		if (unCount == 10) {
			printf("Connection failure");
			return -1;
		}
	}

	// 파일 크기 받기
	unsigned int unFileSize;
	recv(sktSize, (char*)&unFileSize, sizeof(unFileSize), 0);

	// 받은 정보로 파일 생성
	HANDLE hFile = CreateFile
	(
		TEXT("test.txt"),
		GENERIC_WRITE | GENERIC_READ,
		0,
		NULL,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL
	);
	HANDLE hFileMapping = CreateFileMapping
	(
		hFile,
		NULL,
		PAGE_READWRITE,
		0,
		unFileSize,
		NULL
	);
	if (hFileMapping == 0) {
		printe("CreateFileMapping Error", GetLastError());
		return -1;
	}

	pszFile = (char*)MapViewOfFile
	(
		hFileMapping,
		FILE_MAP_WRITE,
		0,
		0,
		unFileSize
	);

	// 데이터 수신 시작
	DWORD dwThreadID;
	HANDLE hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)dataRecv, (SOCKET*)sktData, 0, &dwThreadID);
	if (hThread == NULL) {
		printe("CreateThread Error", GetLastError());
		return -1;
	}
	WaitForSingleObject(hThread, INFINITE);
	puts("File Data Receiving Finish");

	// 받은 파일 사이즈 전송
	unsigned int recvSize = GetFileSize(hFile, NULL);
	retval = send(sktData, (char*)&recvSize, sizeof(recvSize), 0);
	end_time = clock();
	gap = (float)(end_time - start_time) / (CLOCKS_PER_SEC);
	printf("\nTime: %.3f s\n\n", gap);
	printf("\nReceived File Size : %d bytes \n", recvSize);
	CloseHandle(hFileMapping);
	CloseHandle(hFile);
	closesocket(sktSize);
	closesocket(sktData);
	WSACleanup();
}