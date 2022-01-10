#include "Convert.h"

wchar_t* pbzPSZ(const char* _pbz){
	const size_t csi = strlen(_pbz) + 1;
	wchar_t* psz = new wchar_t[csi];
	
	mbstowcs(psz, _pbz, csi);

	return psz;
}

LPCWSTR strLPCWSTR(string _str) {
	wchar_t* buf = new wchar_t[_str.length() + 1];
	copy(_str.begin(), _str.end(), buf);
	buf[_str.length()] = 0;

	return buf;
}

LPCWSTR cpbzLPCWSTR(const char* _cpbz, UINT CodePage) {
	wchar_t* buf = new wchar_t[strlen(_cpbz) + 1];

	if (MultiByteToWideChar(CodePage, 0, _cpbz, -1, buf, strlen(_cpbz) + 1) == 0) {
		// 추후 Window handler로 따로 뺄 예정입니다.
		TCHAR* tmp = 0;
		FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER,
			0, GetLastError(), 0, (TCHAR*)&tmp, 0, 0);

		return buf;
	}

	return buf;
}