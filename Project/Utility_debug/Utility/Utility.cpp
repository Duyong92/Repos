#pragma once
// ���� ���丮���� ã��
#include <io.h>
#include <vector>
#include <string>

// ���� �����쿡 ����
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
    long handle = _findfirst(searching.c_str(), &fd);  //���� ���� �� ��� ������ ã�´�.

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

// TCHAR, wchar ���� ����ϴ� ���� _tmain�� �����ش�.
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

    // CreateFile()���� Ư�� ������ �ҷ��� �����Ű�� ���� CreateFileA()�� �����Ͽ���.
    fHandle = CreateFile(                // HANDLE CreateFile();
        _T("data.txt"),//fileTest,               // LPCTSTR lpFileName, TCHAR Ÿ���� �����̸�
        GENERIC_READ | GENERIC_WRITE, // DWORD dwDesiredAccess, ������� �ϴ� ������ ���� ���� |(or) �� �̿��ؼ� ������ ���� �� �ִ�.
        0,                            // DWORD dwShareMode, �ٸ� ���μ������� �� ���Ͽ� �����Ҷ��� ���� ���������� | ��밡��
        NULL,                         // LPSECURITY_ATTRIBUTES lpSecurityAttributes, ���ȿ� ���õ� ����ü ����. �⺻������ NULL�� ����.
        CREATE_ALWAYS,                // dwCreationDisposition, ������ ���� ���� ���� ������ ������ ��� �������� �����ϴ� �ɼ�.
        0,                            // DWORD dwFlagsAndAttributes, ������ Ư���� �����ϴ� �÷���. ������ ������ ������ ���õȴ�. �Ϲ������� 0
        NULL);                        // HANDLE hTemplateFile, �����ϴ� ������ �������� ���� ������ �ڵ�. �Ϲ������� NULL

    // fHandle = [/]
    
    WriteFile(                           //BOOL WINAPI WriteFile();
        fHandle,                     // HANDLE hFile, ������ ������ �ڵ�.
        _T("abcdefghijklmnopqrs"),   // LPCVOID lpBuffer, �ڵ�� �ٷ�� ���Ͽ� ������� ������
        sizeof(TCHAR) * 13,          // DWORD nNumberOfBytesToWrite, �󸶳� �� ���ΰ�
        NULL,//&result,              // LPDWORD lpNumberOfBytesWritten, �󸶳� �������°��� ���� �����
        NULL                         // LPOVERLAPPED lpOverlapped, ������. NULL�� �Ϲ������� �־���
    );

    curPtr.QuadPart = sizeof(TCHAR) * 4; // ���� ������ ����

    SetFilePointerEx(              // BOOL WINAPI SetFilePointerEx(); ���� ������ �̵��� ������ ���� �Լ�
        fHandle,                   // �ڵ� 
        curPtr,                    // �󸶳� �̵��� ���ΰ�
        NULL,                      // �̵��� ���� ��� ���� �ñ��� ��
        FILE_BEGIN                 // ��� �����ؼ� �̵��� ���ΰ� (FILE_BEGIN, FILE_END,FILE_CURRENT)
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


    //_tprintf(_T("������ ����Ʈ �� : %d\n���� ������ ��ġ : %d\n"), result, curPtr.QuadPart);

    _tprintf(_T("%s\n"), Strings);

    CloseHandle(fHandle);

    return 0;
}

//#include <minwinbase.h>	// WIN32_FIND_DATAW, LPTR, cFileName
//#include <WinUser.h>	// wsprintfw, HANDLE, FILE_ATTRIBUTE_DIRECTORY
//#include <fileapi.h>	// FindFirstFileW, FindNextFileW, FindClose
//#include <handleapi.h>	// INVALID_HANDLE_VALUE
//#include <WinBase.h>	// LocalAlloc
//#include <Windows.h>	// �� ��� ��� ����
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
//	wsprintfW(findFolderPath, L"%s\\*.*", L"C:\\Users\\User\\source\\Repos\\Project\\Utility_debug\\Utility\\");	// wcsFolderFullPath �� ���ڷ� �޴´�
//	HANDLE handle = ::FindFirstFileW(findFolderPath, &fd);  // ���� ���� �� ��� ������ ã�´�.
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