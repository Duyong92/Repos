#pragma warning(disable:4996)
#pragma comment(lib, "Ws2_32.lib")
#include <stdio.h>
#include <io.h>
#include <fcntl.h>
#include <WinSock2.h>
#include <Windows.h>
#include <time.h>

#define BUFSIZE 65536
#define PORT 9090

void errorPrint(const char* message) {
	LPVOID lpMsgBuf;
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, WSAGetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf, 0, NULL);
	printf("[%s] %s", message, (char*)lpMsgBuf);
	LocalFree(lpMsgBuf);
}

const WCHAR* c2wc(const char* _fname) {
	const WCHAR* pwcsName;
	int size = MultiByteToWideChar(CP_ACP, 0, _fname, -1, NULL, 0);
	pwcsName = new WCHAR[256];
	MultiByteToWideChar(CP_ACP, 0, _fname, -1, (LPWSTR)pwcsName, size);
	return pwcsName;
}

HANDLE hFile;
HANDLE hFileMapping;

void WINAPI dataSending(LPVOID arg) {
	SOCKET dataSock = (SOCKET)arg;
	SOCKADDR_IN dataAddr;
	int dataAddrSz = sizeof(dataAddr);
	int retval;

	getpeername(dataSock, (SOCKADDR*)&dataAddr, &dataAddrSz);

	DWORD dwFileSizeHigh;
	__int64 qwFileSize = GetFileSize(hFile, &dwFileSizeHigh);
	__int64 qwFileOffset = 0;

	while (qwFileSize > 0) {
		DWORD dwBytesInBlock = BUFSIZE;
		if (qwFileSize < BUFSIZE) {
			dwBytesInBlock = qwFileSize;
		}

		char* pbFile = (char*)MapViewOfFile
		(
			hFileMapping,
			FILE_MAP_READ,
			(DWORD)(qwFileOffset >> 32),
			(DWORD)(qwFileOffset & 0xFFFFFFFF),
			dwBytesInBlock
		);

		// ���� ����
		retval = send(dataSock, pbFile, dwBytesInBlock, 0);
		if (retval != dwBytesInBlock) {
			while (1) {
				retval = send(dataSock, pbFile, dwBytesInBlock, 0);
				if (retval != 0) break;
			}
		}

		// �並 �� �����Ƿ�, �並 �����Ѵ�.
		UnmapViewOfFile(pbFile);

		// ������ �� ���� ���� ũ�� ����
		qwFileOffset += dwBytesInBlock;
		qwFileSize -= dwBytesInBlock;
	}
}

int main() {
	srand((unsigned)time(NULL));
	char fname [256] = { NULL };
	while (1) {
		printf("Sending File name : ");
		gets_s(fname);

		hFile = CreateFile
		(
			c2wc(fname),	// ���ϸ�
			GENERIC_READ,	// �б�
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
	unsigned int fileSize = GetFileSize(hFile, NULL);
	printf("Sending file Size : %d bytes \n\n", fileSize);

	// WinSock �ʱ�ȭ
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) return -1;

	// Socket ����
	SOCKET mainSock;
	if ((mainSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET) {
		errorPrint("Create Socket Error");
		return -1;
	}

	// ������ ���Ͽ� �ּ� ������ �����Ѵ�.
	SOCKADDR_IN mainSockAddr;
	ZeroMemory(&mainSockAddr, sizeof(mainSockAddr));
	mainSockAddr.sin_family = AF_INET;
	mainSockAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	mainSockAddr.sin_port = htons(PORT);

	// Bind - ���Ͽ� �ּҸ� �Ҵ��Ѵ�.
	int retval;
	if ((retval = bind(mainSock, (SOCKADDR*)&mainSockAddr, sizeof(mainSockAddr))) == SOCKET_ERROR)
		errorPrint("Socket Bind Error");

	// ���� ���� ���� �ɼ� ����
	int sendBuf, sendBufSize = sizeof(sendBuf);
	if ((retval = getsockopt(mainSock, SOL_SOCKET, SO_SNDBUF, (char*)&sendBuf, &sendBufSize)) == SOCKET_ERROR)
		errorPrint("getSockOpt Error");
	printf("Before send buffer size : %d bytes \n", sendBuf);

	sendBuf = BUFSIZE;
	if((retval = setsockopt(mainSock, SOL_SOCKET, SO_SNDBUF, (char*)&sendBuf, sendBufSize)) == SOCKET_ERROR)
		errorPrint("getSockOpt Error");

	if ((retval = getsockopt(mainSock, SOL_SOCKET, SO_SNDBUF, (char*)&sendBuf, &sendBufSize)) == SOCKET_ERROR)
		errorPrint("getSockOpt Error");
	printf("After send buffer size : %d bytes\n", sendBuf);

	// ������ �����·� �����Ѵ�.
	retval = listen(mainSock, 3);
	if (retval == SOCKET_ERROR)
		errorPrint("Socket Listen Error");

	// Ŭ���̾�Ʈ�� ������ ��ٸ�
	puts("\nWaiting for Client...\n");

	// Accept - Ŭ���̾�Ʈ ������ �޾Ƶ��� = Ŭ���̾�Ʈ�� ���� �� ���� ����
	SOCKET sizeSock, dataSock;
	SOCKADDR_IN sizeAddr, dataAddr;
	int sizeAddrSz = sizeof(sizeAddr);
	int dataAddrSz = sizeof(dataAddr);
	while (1) {
		if ((sizeSock = accept(mainSock, (SOCKADDR*)&sizeAddr, &sizeAddrSz)) == INVALID_SOCKET)
			errorPrint("Accept Error");
		else break;
	}
	while (1) {
		if ((dataSock = accept(mainSock, (SOCKADDR*)&dataAddr, &dataAddrSz)) == INVALID_SOCKET)
			errorPrint("Accept Error");
		else break;
	}

	printf("Client Connect from IP : %s, PORT : %d-%d\n\n",
		inet_ntoa(dataAddr.sin_addr), ntohs(sizeAddr.sin_port), ntohs(dataAddr.sin_port));

	// ���� ũ�� ����
	retval = send(sizeSock, (char*)&fileSize, sizeof(fileSize), 0);

	// send - ���� ������ ���� ����
	puts("File Data Sending Start");

	// ���� ����
	hFileMapping = CreateFileMapping
	(
		hFile,	// �� ��ų ������ �ڵ�
		NULL,	// ���� ����
		PAGE_READONLY,	// ���� �Ӽ��� ����
		0,	//  dwMaximumSizeHigh
		0,	// dwMaximumSizeLow
		NULL
	);

	// ���� ������ ����
	DWORD hDataThreadID;
	HANDLE hDataThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)dataSending, (SOCKET*)dataSock, 0, &hDataThreadID);
	WaitForSingleObject(hDataThread, INFINITE);
	puts("File Sengind Finish");
	shutdown(dataSock, SD_SEND);

	// Ŭ���̾�Ʈ���� ���� ���� ������
	unsigned int sendSize;
	if ((retval = recv(dataSock, (char*)&sendSize, sizeof(sendSize), 0)) == SOCKET_ERROR)
		errorPrint("Recv Respone Message Error");

	// Ŭ���̾�Ʈ ������� ���� ������ �� - ������ ����, �ٸ��� ����
	if (sendSize != fileSize)
		puts("File Data Sending Error");
	else
		puts("File Data Sending Complete\n");

	CloseHandle(hFileMapping);
	CloseHandle(hFile);
	closesocket(dataSock);
	closesocket(mainSock);
	WSACleanup();
	return 0;
}