#include "pch.h"
#include <Windows.h>
#include <iostream>
#include "Utility.h"

// Utility ���ٴ� Socket���� ���� ������� ����
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