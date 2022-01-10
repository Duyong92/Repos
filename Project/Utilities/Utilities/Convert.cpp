#include "Convert.h"

wchar_t* pbzPSZ(const char* _pbz)
{
	const size_t csi = strlen(_pbz) + 1;
	wchar_t* psz = new wchar_t[csi];
	
	mbstowcs(psz, _pbz, csi);

	return psz;
}

LPCWSTR pbzLPCWSTR(char* _pbz)
{
	return pbzLPCWSTR((const char*)_pbz);
}

LPCWSTR pbzLPCWSTR(string _str)
{
	return pbzLPCWSTR(_str.c_str());
}

LPCWSTR pbzLPCWSTR(const char* _cpbz)
{
	wchar_t* psz = new wchar_t[sizeof(_cpbz)*2];
	// default ANSI CodePage
	MultiByteToWideChar(CP_ACP, 0, _cpbz, -1, psz, sizeof(_cpbz) * 2);

	return psz;
}