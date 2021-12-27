#pragma warning(disable:4996)
#pragma comment(lib, "Ws2_32.lib")
#include <WS2tcpip.h>
#include <time.h>
#include <iostream>
#include <fstream>

HANDLE hFile;
HANDLE hFileMapping;
int retval;

#define BUFSIZE 65536	// 버퍼 사이즈를 임의로 준다.
#define PORT 9090	// 포트 번호를 임의로 준다.

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

void WINAPI sendData(LPVOID _arg) {
	SOCKET skt = (SOCKET)_arg;
	SOCKADDR_IN sktaddr;
	int sktaddrSize = sizeof(sktaddr);
	int retval;

	// 주소 설정
	if ((retval = getpeername(skt, (SOCKADDR*)&sktaddr, &sktaddrSize)) == SOCKET_ERROR)
		printe("Get Peer Name Error");

	// 파일 크기 측정
	DWORD dwFileSizeHigh;
	__int64 qwFileSize = GetFileSize(hFile, &dwFileSizeHigh);
	__int64 qwFileOffset = 0;

	while (qwFileSize > 0) {
		DWORD dwBytesInBlock = BUFSIZE;
		if (qwFileSize < BUFSIZE)
			dwBytesInBlock = qwFileSize;

		char* pszFile = (char*)MapViewOfFile(
			hFileMapping,
			FILE_MAP_READ,
			(DWORD)(qwFileOffset >> 32),
			(DWORD)(qwFileOffset & 0xFFFFFFFF),
			dwBytesInBlock
		);
		if (pszFile == NULL) {
			printe("MapViewOfFile Error", GetLastError());
			return;
		}

		// 파일 전송
		retval = send(skt, pszFile, dwBytesInBlock, 0);
		if (retval != dwBytesInBlock) {
			while (1) {
				retval = send(skt, pszFile, dwBytesInBlock, 0);
				if (retval != 0) break;
			}
		}

		// 뷰 해제
		UnmapViewOfFile(pszFile);

		// Offset, 남은 파일 크기 갱신
		qwFileOffset += dwBytesInBlock;
		qwFileSize -= dwBytesInBlock;
	}
}

int main(void) {
	// 1970 년도부터의 time 값을 srand 에 할당한다
	srand((unsigned)time(NULL));
	char szFileName[256] = { NULL };

	// 파일 읽기
	while (1) {
		printf("Sending file name : ");
		// file 이름을 입력 받는다.
		gets_s(szFileName);

		// UNICODE 가 설정되어 있다면 CeateFileW
		hFile = CreateFileA(
			szFileName,
			GENERIC_READ,
			0,
			NULL,
			OPEN_EXISTING,
			FILE_FLAG_SEQUENTIAL_SCAN,
			NULL
		);
		if (hFile == INVALID_HANDLE_VALUE) {
			puts("There is no file");
			continue;
		}
		else break;
	}

	// 파일 크기 구하기
	unsigned int unFileSize = GetFileSize(hFile, NULL);
	printf("Sending file size : %d bytes \n\n", unFileSize);

	// Socket 초기화
	WSADATA wsa;
	if ((retval = WSAStartup(MAKEWORD(2, 2), &wsa)) != 0) {
		printe("WSAStartup Error", retval);
		return -1;
	}

	// Socket 생성
	SOCKET skt;
	if ((skt = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET) {
		printe("Create Socket Error");
		return -1;
	}

	// SocketAddress 설정
	SOCKADDR_IN sktaddr;
	ZeroMemory(&sktaddr, sizeof(sktaddr));
	sktaddr.sin_family = AF_INET;
	sktaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	sktaddr.sin_port = htons(PORT);

	// Bind 설정
	if ((retval = bind(skt, (SOCKADDR*)&sktaddr, sizeof(sktaddr))) == SOCKET_ERROR) {
		printe("Socket Bind Error");
		return -1;
	}

	// Socket 옵션 가져오기
	int nSndBuf;
	int nSndBufSize = sizeof(nSndBuf);
	if ((retval = getsockopt(skt, SOL_SOCKET, SO_SNDBUF, (char*)&nSndBuf, &nSndBufSize)) == SOCKET_ERROR)
		printe("getSockOpt Error");
	printf("Before send buffer size : %d bytes \n", nSndBuf);

	// Socket 옵션 설정
	nSndBuf = BUFSIZE;
	retval = setsockopt(skt, SOL_SOCKET, SO_SNDBUF, (char*)&nSndBuf, nSndBufSize);

	// Socket 옵션 다시 가져오기
	if ((retval = getsockopt(skt, SOL_SOCKET, SO_SNDBUF, (char*)&nSndBuf, &nSndBufSize)) == SOCKET_ERROR)
		printe("getSockOpt Error");
	printf("After send buffer size : %d bytes \n", nSndBuf);

	// Socket Listen
	if ((retval = listen(skt, SOMAXCONN) == SOCKET_ERROR)) {
		printe("Socket Listen Error");
		return -1;
	}

	// Client 대기
	puts("\nWaiting for Client...\n");

	// Accept Client
	SOCKET sktSize, sktData;
	SOCKADDR_IN sktaddrSize, sktaddrData;
	int unsktaddrSizeSize = sizeof(sktaddrSize);
	int unsktaddrDataSize = sizeof(sktaddrData);

	while (1) {
		if ((sktSize = accept(skt, (SOCKADDR*)&sktaddrSize, &unsktaddrSizeSize)) == INVALID_SOCKET) {
			printe("Accept Error");
			return -1;
		}
		else break;
	}
	while (1) {
		if ((sktData = accept(skt, (SOCKADDR*)&sktaddrData, &unsktaddrDataSize)) == INVALID_SOCKET) {
			printe("Accept Error");
			return -1;
		}
		else break;
	}

	printf("Client Connect from IP : %s, Port : %d-%d\n\n",
		inet_ntoa(sktaddrData.sin_addr), ntohs(sktaddrSize.sin_port), ntohs(sktaddrData.sin_port));

	// 파일 크기 전송
	if ((retval = send(sktSize, (char*)&unFileSize, sizeof(unFileSize), 0)) == SOCKET_ERROR) {
		printe("Send Error", GetLastError());
		return -1;
	}

	// 파일 전송 대기
	puts("File Data Sending Start..");

	// File Mapping
	hFileMapping = CreateFileMapping(
		hFile,	// 매핑할 파일
		NULL,	// 보안 설정
		PAGE_READONLY,	// 파일 속성
		0,	// dwMaximumSizeHigh
		0,	// dwMaximumSizeLow
		NULL
	);

	// 수신 스레드 생성
	DWORD dwThreadID;
	HANDLE hThread = CreateThread(
		NULL, // Thread kernel object 보안 특성 기본 'NULL'
		0,	// Thread stack 크기 디폴트 '0'
		(LPTHREAD_START_ROUTINE)sendData,	// 실행되는 함수
		(SOCKET*)sktData,	// 실행되는 함수 넘겨지는 매개변수
		0, // 스레드 제어하는 플래그
		&dwThreadID	// 스레드의 ID 값
	);
	if (hThread == NULL) {
		printe("CreateThread Error", GetLastError());
		return 0;
	}

	WaitForSingleObject(hThread, INFINITE);
	puts("File Sending Finish");
	shutdown(sktData, SD_SEND);

	return 0;
}