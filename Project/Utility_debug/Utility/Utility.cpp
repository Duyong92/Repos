#pragma once
// 파일 디렉토리에서 찾기
#include <io.h>
#include <vector>
#include <string>

// 파일 윈도우에 열기
#include <iostream>
#include <Windows.h>
#include <tchar.h>  // LPCTSTR(Long Point Constant Tstring), Tchar
#include <locale.h>

// find all matched file in specified directory
// [INPUT]
//   >> const std::string& _path        Search path        ex) c:/directory/
//   >> const std::string& _filter        Search filter    ex) *.exe or *.*
// [RETURN]
//   >> std::vector<std::string>        All matched file name & extension
std::vector<std::string> get_files_inDirectory(const std::string& _path, const std::string& _filter)
{
    std::string searching = _path + _filter;

    std::vector<std::string> return_;

    _finddata_t fd;
    long handle = _findfirst(searching.c_str(), &fd);  //현재 폴더 내 모든 파일을 찾는다.

    if (handle == -1)    return return_;

    int result = 0;
    do
    {
        printf(fd.name);
        printf("\n");
        return_.push_back(fd.name);
        result = _findnext(handle, &fd);
    } while (result != -1);

    _findclose(handle);

    return return_;
}

// TCHAR, wchar 등을 사용하는 경우는 _tmain을 열어준다.
int _tmain(int argc, LPSTR argv[]) 
{
    //std::string tmp = get_files_inDirectory("C:\\Users\\User\\source\\Repos\\Project\\Utility_debug\\Utility\\", "test.txt")[0];
    //LPCSTR fileTest = (LPCSTR)tmp.c_str();
    
    HANDLE fHandle;
    TCHAR Strings[] = _T("AABBCCDDEEFFGGHHIIJJKKLLMMNNOOPP");
    //DWORD result;
    LARGE_INTEGER curPtr;
    _wsetlocale(
        LC_ALL,
        _T("Korean")
    );

    // CreateFile()에서 특정 파일을 불러와 실행시키기 위해 CreateFileA()로 변경하였다.
    fHandle = CreateFile(                // HANDLE CreateFile();
        _T("data.txt"),//fileTest,               // LPCTSTR lpFileName, TCHAR 타입의 파일이름
        GENERIC_READ | GENERIC_WRITE, // DWORD dwDesiredAccess, 만들고자 하는 파일의 접근 권한 |(or) 를 이용해서 여러개 적을 수 있다.
        0,                            // DWORD dwShareMode, 다른 프로세스에서 이 파일에 접근할때의 권한 마찬가지로 | 사용가능
        NULL,                         // LPSECURITY_ATTRIBUTES lpSecurityAttributes, 보안에 관련된 구조체 설정. 기본적으로 NULL을 쓴다.
        CREATE_ALWAYS,                // dwCreationDisposition, 파일을 새로 만들어서 열지 기존의 파일을 열어서 수정할지 결정하는 옵션.
        0,                            // DWORD dwFlagsAndAttributes, 파일의 특성을 지정하는 플래그. 기존의 파일을 열때는 무시된다. 일반적으로 0
        NULL);                        // HANDLE hTemplateFile, 존재하는 파일을 열었을때 기존 파일의 핸들. 일반적으로 NULL

    // fHandle = [/]
    
    WriteFile(                           //BOOL WINAPI WriteFile();
        fHandle,                     // HANDLE hFile, 만들어둔 파일의 핸들.
        _T("abcdefghijklmnopqrs"),   // LPCVOID lpBuffer, 핸들로 다루는 파일에 쓰고싶은 데이터
        sizeof(TCHAR) * 13,          // DWORD nNumberOfBytesToWrite, 얼마나 쓸 것인가
        NULL,//&result,              // LPDWORD lpNumberOfBytesWritten, 얼마나 쓰여졌는가에 대한 결과값
        NULL                         // LPOVERLAPPED lpOverlapped, 어려운거. NULL을 일반적으로 넣어줌
    );

    curPtr.QuadPart = sizeof(TCHAR) * 4; // 파일 포인터 조정

    SetFilePointerEx(              // BOOL WINAPI SetFilePointerEx(); 파일 내에서 이동할 포인터 조작 함수
        fHandle,                   // 핸들 
        curPtr,                    // 얼마나 이동할 것인가
        NULL,                      // 이동이 끝난 결과 값이 궁금할 때
        FILE_BEGIN                 // 어디서 시작해서 이동할 것인가 (FILE_BEGIN, FILE_END,FILE_CURRENT)
    );

    _tprintf(_T("%s\n"), Strings);

    ReadFile(                            // BOOL WINAPI ReadFile()
        fHandle,                         // HANDLE hFile,
        Strings,                         // LPVOID lpBuffer,
        sizeof(TCHAR) * 7,                 // DWORD nNumberOfBytesToRead,
        NULL,//&result,                         // LPDWORD lpNumberOfBytesRead,
        NULL                             // LPOVERLAPPED lpOverlapped,
    );
    //     curPtr      |------>|
    // fHandle = [ abcd efghijk lm]


    //_tprintf(_T("읽혀진 바이트 수 : %d\n현재 포인터 위치 : %d\n"), result, curPtr.QuadPart);

    _tprintf(_T("%s\n"), Strings);

    CloseHandle(fHandle);

    return 0;
}

//#include <minwinbase.h>	// WIN32_FIND_DATAW, LPTR, cFileName
//#include <WinUser.h>	// wsprintfw, HANDLE, FILE_ATTRIBUTE_DIRECTORY
//#include <fileapi.h>	// FindFirstFileW, FindNextFileW, FindClose
//#include <handleapi.h>	// INVALID_HANDLE_VALUE
//#include <WinBase.h>	// LocalAlloc
//#include <Windows.h>	// 위 모든 헤더 포함
//#include <vector> // vector
//
//using namespace std;
//
//#define MAX_PATH 260
//
//int main()
//{
//	vector<wchar_t*> vec;
//	int nresult = -1;
//	WIN32_FIND_DATAW fd;
//	wchar_t findFolderPath[MAX_PATH];
//	wsprintfW(findFolderPath, L"%s\\*.*", L"C:\\Users\\User\\source\\Repos\\Project\\Utility_debug\\Utility\\");	// wcsFolderFullPath 는 인자로 받는다
//	HANDLE handle = ::FindFirstFileW(findFolderPath, &fd);  // 현재 폴더 내 모든 파일을 찾는다.
//
//	if (handle != INVALID_HANDLE_VALUE)
//	{
//		do {
//			if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
//				wchar_t* tmp = (wchar_t*)LocalAlloc(LPTR, sizeof(fd.cFileName));
//				wprintf(L"%s\n", tmp);
//				wcscpy_s(tmp, wcslen(fd.cFileName) * 2, fd.cFileName);
//				vec.push_back(tmp);
//			}
//		} while (::FindNextFileW(handle, &fd));
//		::FindClose(handle);
//	}
//
//	return 0;
//}