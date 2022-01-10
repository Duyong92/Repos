#pragma warning(disable:4996)
#pragma once
#include <Windows.h>
#include <string>

using namespace std;

wchar_t* pbzPSZ(const char* _pbz);

LPCWSTR strLPCWSTR(string _str);

LPCWSTR cpbzLPCWSTR(const char* _cpbz, UINT CodePage = CP_ACP);