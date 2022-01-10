#pragma warning(disable:4996)
#pragma once
#include <Windows.h>
#include <string>

using namespace std;

wchar_t* pbzPSZ(const char* _pbz);

LPCWSTR pbzLPCWSTR(char* _pbz);
LPCWSTR pbzLPCWSTR(string _str);
LPCWSTR pbzLPCWSTR(const char* _cpbz);