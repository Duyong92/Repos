#pragma warning(disable:4996)
#pragma comment(lib, "Ws2_32.lib")
#include <WS2tcpip.h>
#include <time.h>
#include <iostream>
#include <fstream>

HANDLE hFile;
HANDLE hFileMapping;
int retval;

#define BUFSIZE 65536	// ���� ����� ���Ƿ� �ش�.
#define PORT 9090	// ��Ʈ ��ȣ�� ���Ƿ� �ش�.

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

	// �ּ� ����
	if ((retval = getpeername(skt, (SOCKADDR*)&sktaddr, &sktaddrSize)) == SOCKET_ERROR)
		printe("Get Peer Name Error");

	// ���� ũ�� ����
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

		// ���� ����
		retval = send(skt, pszFile, dwBytesInBlock, 0);
		if (retval != dwBytesInBlock) {
			while (1) {
				retval = send(skt, pszFile, dwBytesInBlock, 0);
				if (retval != 0) break;
			}
		}

		// �� ����
		UnmapViewOfFile(pszFile);

		// Offset, ���� ���� ũ�� ����
		qwFileOffset += dwBytesInBlock;
		qwFileSize -= dwBytesInBlock;
	}
}

int main(void) {
	// 1970 �⵵������ time ���� srand �� �Ҵ��Ѵ�
	srand((unsigned)time(NULL));
	char szFileName[256] = { NULL };

	// ���� �б�
	while (1) {
		printf("Sending file name : ");
		// file �̸��� �Է� �޴´�.
		gets_s(szFileName);

		// UNICODE �� �����Ǿ� �ִٸ� CeateFileW
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

	// ���� ũ�� ���ϱ�
	unsigned int unFileSize = GetFileSize(hFile, NULL);
	printf("Sending file size : %d bytes \n\n", unFileSize);

	// Socket �ʱ�ȭ
	WSADATA wsa;
	if ((retval = WSAStartup(MAKEWORD(2, 2), &wsa)) != 0) {
		printe("WSAStartup Error", retval);
		return -1;
	}

	// Socket ����
	SOCKET skt;
	if ((skt = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET) {
		printe("Create Socket Error");
		return -1;
	}

	// SocketAddress ����
	SOCKADDR_IN sktaddr;
	ZeroMemory(&sktaddr, sizeof(sktaddr));
	sktaddr.sin_family = AF_INET;
	sktaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	sktaddr.sin_port = htons(PORT);

	// Bind ����
	if ((retval = bind(skt, (SOCKADDR*)&sktaddr, sizeof(sktaddr))) == SOCKET_ERROR) {
		printe("Socket Bind Error");
		return -1;
	}

	// Socket �ɼ� ��������
	int nSndBuf;
	int nSndBufSize = sizeof(nSndBuf);
	if ((retval = getsockopt(skt, SOL_SOCKET, SO_SNDBUF, (char*)&nSndBuf, &nSndBufSize)) == SOCKET_ERROR)
		printe("getSockOpt Error");
	printf("Before send buffer size : %d bytes \n", nSndBuf);

	// Socket �ɼ� ����
	nSndBuf = BUFSIZE;
	retval = setsockopt(skt, SOL_SOCKET, SO_SNDBUF, (char*)&nSndBuf, nSndBufSize);

	// Socket �ɼ� �ٽ� ��������
	if ((retval = getsockopt(skt, SOL_SOCKET, SO_SNDBUF, (char*)&nSndBuf, &nSndBufSize)) == SOCKET_ERROR)
		printe("getSockOpt Error");
	printf("After send buffer size : %d bytes \n", nSndBuf);

	// Socket Listen
	if ((retval = listen(skt, SOMAXCONN) == SOCKET_ERROR)) {
		printe("Socket Listen Error");
		return -1;
	}

	// Client ���
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

	// ���� ũ�� ����
	if ((retval = send(sktSize, (char*)&unFileSize, sizeof(unFileSize), 0)) == SOCKET_ERROR) {
		printe("Send Error", GetLastError());
		return -1;
	}

	// ���� ���� ���
	puts("File Data Sending Start..");

	// File Mapping
	hFileMapping = CreateFileMapping(
		hFile,	// ������ ����
		NULL,	// ���� ����
		PAGE_READONLY,	// ���� �Ӽ�
		0,	// dwMaximumSizeHigh
		0,	// dwMaximumSizeLow
		NULL
	);

	// ���� ������ ����
	DWORD dwThreadID;
	HANDLE hThread = CreateThread(
		NULL, // Thread kernel object ���� Ư�� �⺻ 'NULL'
		0,	// Thread stack ũ�� ����Ʈ '0'
		(LPTHREAD_START_ROUTINE)sendData,	// ����Ǵ� �Լ�
		(SOCKET*)sktData,	// ����Ǵ� �Լ� �Ѱ����� �Ű�����
		0, // ������ �����ϴ� �÷���
		&dwThreadID	// �������� ID ��
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