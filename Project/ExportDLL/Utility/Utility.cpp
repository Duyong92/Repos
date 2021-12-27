#include "pch.h"
#include <Windows.h>
#include <iostream>
#include "Utility.h"

// Utility 보다는 Socket으로 따로 만들어줄 예정
void errorPrint(const char* message) {
	LPVOID lpMsgBuf;
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, WSAGetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf, 0, NULL);
	printf("[%s] %s", message, (char*)lpMsgBuf);
	LocalFree(lpMsgBuf);
	return;
}