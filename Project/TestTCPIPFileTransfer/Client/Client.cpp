#pragma warning(disable:4996)
#pragma comment(lib, "Ws2_32.lib")
#include <stdio.h>
#include <io.h>
#include <fcntl.h>
#include <WinSock2.h>
#include <Windows.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#define BUFSIZE 65536
#define PORT 9090
#define IP "127.0.0.1"

char* pbFile2;

void WINAPI dataRecv(LPVOID arg) {
	SOCKET dataSock = (SOCKET)arg;
	SOCKADDR_IN dataAddr;
	int dataAddrSz = sizeof(dataAddr);
	int retval;
	getpeername(dataSock, (SOCKADDR*)&dataAddr, &dataAddrSz);
	do {
		retval = recv(dataSock, pbFile2, BUFSIZE, 0);
		pbFile2 += retval;
		if (retval == 0)
			break;
		else if (retval == SOCKET_ERROR)
			break;
	} while (retval > 0);
}

int main() {
	time_t start_time, end_time;
	float gap;
	start_time = clock();	// 시작 시간 측정

	//WinSock 초기화
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return -1;

	// Socket 생성
	SOCKET sizeSock, dataSock;
	sizeSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	dataSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	// 수신 소켓 주소 정보 설정
	SOCKADDR_IN sizeAddr, dataAddr;
	int sizeAddrSz = sizeof(sizeAddr);
	int dataAddrSz = sizeof(dataAddr);
	
	ZeroMemory(&sizeAddr, sizeAddrSz);
	sizeAddr.sin_family = AF_INET;
	sizeAddr.sin_addr.s_addr = inet_addr(IP);
	sizeAddr.sin_port = htons(PORT);

	ZeroMemory(&dataAddr, dataAddrSz);
	dataAddr.sin_family = AF_INET;
	dataAddr.sin_addr.s_addr = inet_addr(IP);
	dataAddr.sin_port = htons(PORT);

	// 소켓 옵션 설정 -  수신 버퍼 크기 설정
	int retval, recvBuf = BUFSIZE;
	retval = setsockopt(dataSock, SOL_SOCKET, SO_RCVBUF, (char*)&recvBuf, sizeof(recvBuf));
	printf("Recv buffer size : %d bytes\n", recvBuf);

	// Nagle 알고리즘
	int opt_val = TRUE;
	setsockopt(dataSock, IPPROTO_TCP, TCP_NODELAY, (char*)opt_val, sizeof(opt_val));

	// Connet - 서버 측에 연결 요청
	retval = connect(sizeSock, (SOCKADDR*)&sizeAddr, sizeAddrSz);
	if((retval = connect(dataSock,(SOCKADDR*)&dataAddr, dataAddrSz)) == SOCKET_ERROR)
		printf("Error : %d\n", WSAGetLastError());
	
	// 파일 크기 받기
	unsigned int fileSize;
	recv(sizeSock, (char*)&fileSize, sizeof(fileSize), 0);

	// 받은 정보로 파일 생성
	HANDLE hFile2 = CreateFile
	(
		TEXT("test.txt"),
		GENERIC_WRITE | GENERIC_READ,
		0,
		NULL,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL
	);
	HANDLE hFileMapping2 = CreateFileMapping
	(
		hFile2,
		NULL,
		PAGE_READWRITE,
		0,
		fileSize,
		NULL
	);
	pbFile2 = (char*)MapViewOfFile
	(
		hFileMapping2,
		FILE_MAP_WRITE,
		0,
		0,
		fileSize
	);

	// 데이터 수신 시작
	DWORD hThreadID;
	HANDLE hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)dataRecv, (SOCKET*)dataSock, 0, &hThreadID);
	WaitForSingleObject(hThread, INFINITE);
	puts("File Data Receiving Finish");

	// 받은 파일 사이즈 전송
	unsigned int recvSize = GetFileSize(hFile2, NULL);
	retval = send(dataSock, (char*)&recvSize, sizeof(recvSize), 0);
	end_time = clock();
	gap = (float)(end_time - start_time) / (CLOCKS_PER_SEC);
	printf("\nTime: %.3f s\n\n", gap);
	printf("\nReceived File Size : %d bytes \n", recvSize);
	CloseHandle(hFileMapping2);
	CloseHandle(hFile2);
	closesocket(sizeSock);
	closesocket(dataSock);
	WSACleanup();
}