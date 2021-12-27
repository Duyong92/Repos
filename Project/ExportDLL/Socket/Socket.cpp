#include "pch.h"

#pragma comment(lib, "Ws2_32.lib")
#include <WinSock2.h>
#include <Windows.h>
#include <iostream>

#include "Socket.h"

namespace Socket {
#define BUFSIZE 65536
#define PORT 9090	// D1223 ����ڰ� �����ϰԲ� �ٲٱ�

	/// <summary>
	/// ���� �޽��� Id ���� �޾� �߰��� �޽����� �Բ� ���ڿ��� ����Ѵ�.
	/// </summary>
	/// <param name="_message">���� ����� �޽����̴�.</param>
	/// <param name="_dwMessageId">���ڿ��� �ް� ���� ���� �޽��� Id ���̴�.</param>
	/// <returns>void</returns>
	void printError(const char* _message, DWORD _dwMessageId) {
		LPVOID lpMsgBuf;	// �ӽ� ���� �޼��� ���ڿ� ����
		FormatMessage(
			FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
			NULL, _dwMessageId,
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
			(LPTSTR)&lpMsgBuf, 0, NULL);
		printf("[%s] %s", _message, (char*)lpMsgBuf);
		LocalFree(lpMsgBuf);
	}
	/// <summary>
	/// connect, accept �� ���Ͽ� �ڵ� ���� ������ �Էµ� ���¿� ���� ���� �並 �����Ͽ� ������ �۽��Ѵ�.
	/// </summary>
	/// <param name="_socket">����� ���� ��ũ�����̴�.</param>
	/// <param name="hFile">�۽��� �ڵ� �����̴�.</param>
	/// <param name="hFileMapping">�ڵ� ���� �����̴�.</param>
	/// <returns>void</returns>
	void WINAPI sendData(LPVOID _socket, HANDLE _hFile, HANDLE _hFileMapping) {
		SOCKET dataSock = (SOCKET)_socket;	// ����
		SOCKADDR_IN dataAddr;	// ���� �ּ�
		int dataAddrSz = sizeof(dataAddr);	// ������ ũ��
		int retval;	// ��ȯ ��

		// connect, accept �� ���Ͽ� ����� ��� �ý����� �ּҸ� ��ȯ �Ѵ�.
		getpeername(dataSock, (SOCKADDR*)&dataAddr, &dataAddrSz);

		DWORD dwFileSizeHigh;	// ���� ũ�Ⱚ(high-order)
		DWORD qwFileSize;		// ���� ũ�Ⱚ(low-order)
		if ((qwFileSize = GetFileSize(_hFile, &dwFileSizeHigh)) == 0xFFFFFFFF)
			printError("GetFileSize", GetLastError());
		DWORD qwFileOffset = 0;	// ���� �����°�

		// ���� ũ�Ⱚ�� �������� ��
		while (qwFileSize > 0) {
			// BUFSIZE �� �۽��� ���� ũ�⸦ �ʱ�ȭ�Ѵ�.
			DWORD dwBytesInBlock = BUFSIZE;
			// ���� ũ�Ⱑ BUFSIZE ���� ���� �� ���� ũ�⸦ �Ҵ��Ѵ�.
			if (qwFileSize < BUFSIZE)
				dwBytesInBlock = qwFileSize;

			// �� ����
			char* pbFile = (char*)MapViewOfFile
			(
				_hFileMapping,
				FILE_MAP_READ,
				(DWORD)(qwFileOffset >> 32),
				(DWORD)(qwFileOffset & 0xFFFFFFFF),
				dwBytesInBlock
			);

			// pbFile �� 0�� ��� �����Ѵ�.
			if (pbFile == 0) {
				printf("File Missing.");
				return;
			}

			// ���� ����
			retval = send(dataSock, pbFile, dwBytesInBlock, 0);
			if (retval != dwBytesInBlock) {
				while (1) {
					retval = send(dataSock, pbFile, dwBytesInBlock, 0);	// ?
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
	char* WINAPI dataRecv(LPVOID arg, HANDLE _hFile, HANDLE _hFileMapping) {
		char* pbFile;
		SOCKET dataSock = (SOCKET)arg;
		SOCKADDR_IN dataAddr;
		int dataAddrSize = sizeof(dataAddr);
		int retval;
		getpeername(dataSock, (SOCKADDR*)&dataAddr, &dataAddrSize);
		do {
			retval = recv(dataSock, pbFile, BUFSIZE, 0);
			pbFile += retval;
		}
	}
}