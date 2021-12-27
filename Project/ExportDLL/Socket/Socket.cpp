#include "pch.h"

#pragma comment(lib, "Ws2_32.lib")
#include <WinSock2.h>
#include <Windows.h>
#include <iostream>

#include "Socket.h"

namespace Socket {
#define BUFSIZE 65536
#define PORT 9090	// D1223 사용자가 설정하게끔 바꾸기

	/// <summary>
	/// 에러 메시지 Id 값을 받아 추가할 메시지와 함께 문자열로 출력한다.
	/// </summary>
	/// <param name="_message">같이 출력할 메시지이다.</param>
	/// <param name="_dwMessageId">문자열로 받고 싶은 에러 메시지 Id 값이다.</param>
	/// <returns>void</returns>
	void printError(const char* _message, DWORD _dwMessageId) {
		LPVOID lpMsgBuf;	// 임시 에러 메세지 문자열 버퍼
		FormatMessage(
			FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
			NULL, _dwMessageId,
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
			(LPTSTR)&lpMsgBuf, 0, NULL);
		printf("[%s] %s", _message, (char*)lpMsgBuf);
		LocalFree(lpMsgBuf);
	}
	/// <summary>
	/// connect, accept 된 소켓에 핸들 파일 매핑의 입력된 상태에 따라 맵의 뷰를 생성하여 파일을 송신한다.
	/// </summary>
	/// <param name="_socket">사용할 소켓 디스크립터이다.</param>
	/// <param name="hFile">송신할 핸들 파일이다.</param>
	/// <param name="hFileMapping">핸들 파일 매핑이다.</param>
	/// <returns>void</returns>
	void WINAPI sendData(LPVOID _socket, HANDLE _hFile, HANDLE _hFileMapping) {
		SOCKET dataSock = (SOCKET)_socket;	// 소켓
		SOCKADDR_IN dataAddr;	// 소켓 주소
		int dataAddrSz = sizeof(dataAddr);	// 데이터 크기
		int retval;	// 반환 값

		// connect, accept 된 소켓에 연결된 상대 시스템의 주소를 반환 한다.
		getpeername(dataSock, (SOCKADDR*)&dataAddr, &dataAddrSz);

		DWORD dwFileSizeHigh;	// 파일 크기값(high-order)
		DWORD qwFileSize;		// 파일 크기값(low-order)
		if ((qwFileSize = GetFileSize(_hFile, &dwFileSizeHigh)) == 0xFFFFFFFF)
			printError("GetFileSize", GetLastError());
		DWORD qwFileOffset = 0;	// 파일 오프셋값

		// 파일 크기값을 추출했을 때
		while (qwFileSize > 0) {
			// BUFSIZE 로 송신할 파일 크기를 초기화한다.
			DWORD dwBytesInBlock = BUFSIZE;
			// 파일 크기가 BUFSIZE 보다 작을 때 파일 크기를 할당한다.
			if (qwFileSize < BUFSIZE)
				dwBytesInBlock = qwFileSize;

			// 뷰 생성
			char* pbFile = (char*)MapViewOfFile
			(
				_hFileMapping,
				FILE_MAP_READ,
				(DWORD)(qwFileOffset >> 32),
				(DWORD)(qwFileOffset & 0xFFFFFFFF),
				dwBytesInBlock
			);

			// pbFile 이 0일 경우 종료한다.
			if (pbFile == 0) {
				printf("File Missing.");
				return;
			}

			// 파일 전송
			retval = send(dataSock, pbFile, dwBytesInBlock, 0);
			if (retval != dwBytesInBlock) {
				while (1) {
					retval = send(dataSock, pbFile, dwBytesInBlock, 0);	// ?
					if (retval != 0) break;
				}
			}

			// 뷰를 다 썼으므로, 뷰를 해제한다.
			UnmapViewOfFile(pbFile);

			// 오프셋 및 남은 파일 크기 갱신
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