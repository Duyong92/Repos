#pragma once
#pragma warning(disable:4996)

#ifdef SOCKET_EXPORTS
#define SOCKET_API __declspec(dllexport)
#else
#define SOCKET_API __declspec(dllimport)
#endif
namespace Socket {
	extern "C" SOCKET_API void printError(const char* _message, DWORD _dwMessageId = WSAGetLastError());
	extern "C" SOCKET_API void WINAPI sendData(LPVOID _socket, HANDLE hFile, HANDLE hFileMapping);
}