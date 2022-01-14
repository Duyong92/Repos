#pragma warning(disable:4996)
// Xl.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <ole2.h> // OLE2 Definitions

wchar_t* pbzPSZ(const char* _pbz) {
    wchar_t* psz;

    int n = MultiByteToWideChar(CP_ACP, 0, _pbz, -1, NULL, NULL);

    psz = new WCHAR[n];

    MultiByteToWideChar(CP_ACP, 0, _pbz, strlen(_pbz)+1, psz, n);

    return psz;
}

// AutoWrap() - Automation helper function...
HRESULT AutoWrap(int autoType, VARIANT* pvResult, IDispatch* pDisp, LPOLESTR ptName, int cArgs...) {
    // Begin variable-argument list...
    va_list marker;
    va_start(marker, cArgs);

    if (!pDisp) {
        MessageBoxA(NULL, "NULL IDispatch passed to AutoWrap()", "Error", 0x10010);
        _exit(0);
    }

    // Variables used...
    DISPPARAMS dp = { NULL, NULL, 0, 0 };
    DISPID dispidNamed = DISPID_PROPERTYPUT;
    DISPID dispID;
    HRESULT hr;
    char buf[256];
    char szName[256];


    // Convert down to ANSI
    WideCharToMultiByte(CP_ACP, 0, ptName, -1, szName, 256, NULL, NULL);

    // Get DISPID for name passed...
    hr = pDisp->GetIDsOfNames(IID_NULL, &ptName, 1, LOCALE_USER_DEFAULT, &dispID);
    if (FAILED(hr)) {
        sprintf(buf, "IDispatch::GetIDsOfNames(\"%s\") failed w/err 0x%08lx", szName, hr);
        MessageBoxA(NULL, buf, "AutoWrap()", 0x10010);
        _exit(0);
        return hr;
    }

    // Allocate memory for arguments...
    VARIANT* pArgs = new VARIANT[(size_t)cArgs + 1];
    // Extract arguments...
    for (int i = 0; i < cArgs; i++) {
        pArgs[i] = va_arg(marker, VARIANT);
    }

    // Build DISPPARAMS
    dp.cArgs = cArgs;
    dp.rgvarg = pArgs;

    // Handle special-case for property-puts!
    if (autoType & DISPATCH_PROPERTYPUT) {
        dp.cNamedArgs = 1;
        dp.rgdispidNamedArgs = &dispidNamed;
    }

    // Make the call!
    hr = pDisp->Invoke(dispID, IID_NULL, LOCALE_SYSTEM_DEFAULT, autoType, &dp, pvResult, NULL, NULL);
    if (FAILED(hr)) {
        sprintf(buf, "IDispatch::Invoke(\"%s\"=%08lx) failed w/err 0x%08lx", szName, dispID, hr);
        MessageBoxA(NULL, buf, "AutoWrap()", 0x10010);
        _exit(0);
        return hr;
    }
    // End variable-argument section...
    va_end(marker);

    delete[] pArgs;

    return hr;
}


int main()
{
    // Initialize COM for this thread...
    HRESULT hr = CoInitialize(NULL);
    
    if (FAILED(hr)) 
    {
        ::MessageBoxA(NULL, "Colntialize() failed", "Error", 0x10010);
        return -1;
    }

    // Get CLSID for our server...
    CLSID clsid;
    hr = CLSIDFromProgID(L"Excel.Application", &clsid);

    if (FAILED(hr)) 
    {
        ::MessageBoxA(NULL, "CLSIDFromProgID() failed", "Error", 0x10010);
        return -2;
    }

    // Start server and get IDispatch...
    IDispatch* pXlApp;
    hr = CoCreateInstance(clsid, NULL, CLSCTX_LOCAL_SERVER, IID_IDispatch, (void**)&pXlApp);
    if (FAILED(hr)) 
    {
        ::MessageBoxA(NULL, "Excel not registered properly", "Error", 0x10010);
        return -2;
    }

    // Make it visible (i.e. app.visible = 1)
    {
        VARIANT x;
        x.vt = VT_I4;
        x.lVal = 1;
        AutoWrap(DISPATCH_PROPERTYPUT, NULL, pXlApp, pbzPSZ("Visible"), 1, x);
    }

    // Get Workbooks collection
    IDispatch* pXlBooks;
    {
        VARIANT result;
        VariantInit(&result);
        AutoWrap(DISPATCH_PROPERTYGET, &result, pXlApp, pbzPSZ("Workbooks"), 0);
        pXlBooks = result.pdispVal;
    }

    // Call Workbooks.Add() to get a new workbook...
    IDispatch* pXlBook;
    {
        VARIANT result;
        VariantInit(&result);
        AutoWrap(DISPATCH_PROPERTYGET, &result, pXlBooks, pbzPSZ("Add"), 0);
        pXlBook = result.pdispVal;
    }

    // Create a 15x15 safearray of variants...
    VARIANT arr;
    arr.vt = VT_ARRAY | VT_VARIANT;
    {
        SAFEARRAYBOUND sab[2];
        sab[0].lLbound = 1; sab[0].cElements = 15;
        sab[1].lLbound = 1; sab[1].cElements = 15;
        arr.parray = SafeArrayCreate(VT_VARIANT, 2, sab);
    }

    // Fill safearray with some values...
    for (int i = 1; i <= 15; i++) {
        for (int j = 1; j <= 15; j++) {
            // Create entry value for (i,j)
            VARIANT tmp;
            tmp.vt = VT_I4;
            tmp.lVal = i * j;
            // Add to safearray...
            long indices[] = { i,j };
            hr = SafeArrayPutElement(arr.parray, indices, (void*)&tmp);

            if (FAILED(hr))
            {
                ::MessageBoxA(NULL, "Colntialize() failed", "Error", 0x10010);
                return -1;
            }
        }
    }

    // Get ActiveSheet object
    IDispatch* pXlSheet;
    {
        VARIANT result;
        VariantInit(&result);
        AutoWrap(DISPATCH_PROPERTYGET, &result, pXlApp, pbzPSZ("ActiveSheet"), 0);
        pXlSheet = result.pdispVal;
    }

    // Get Range object for the Range A1:O15...
    IDispatch* pXlRange;
    {
        VARIANT parm;
        parm.vt = VT_BSTR;
        parm.bstrVal = ::SysAllocString(L"A1:O15");

        VARIANT result;
        VariantInit(&result);
        AutoWrap(DISPATCH_PROPERTYGET, &result, pXlSheet, pbzPSZ("Range"), 1, parm);
        VariantClear(&parm);

        pXlRange = result.pdispVal;
    }

    // Set range with our safearray...
    AutoWrap(DISPATCH_PROPERTYPUT, NULL, pXlRange, pbzPSZ("Value"), 1, arr);

    // Wait for user...
    ::MessageBoxA(NULL, "All done.", "Notice", 0x10000);

    // Set .Saved property of workbook to TRUE so we aren't prompted
    // to save when we tell Excel to quit...
    {
        VARIANT x;
        x.vt = VT_I4;
        x.lVal = 1;
        AutoWrap(DISPATCH_PROPERTYPUT, NULL, pXlBook, pbzPSZ("Saved"), 1, x);
    }

    // Tell Excel to quit (i.e. App.Quit)
    AutoWrap(DISPATCH_METHOD, NULL, pXlApp, pbzPSZ("Quit"), 0);

    // Release references...
    pXlRange->Release();
    pXlSheet->Release();
    pXlBook->Release();
    pXlBooks->Release();
    pXlApp->Release();
    VariantClear(&arr);

    

    Sleep(2000);
    // Uninitialize COM for this thread...
    CoUninitialize();

    std::cout << "Hello World!\n";
}

// 프로그램 실행: <Ctrl+F5> 또는 [디버그] > [디버깅하지 않고 시작] 메뉴
// 프로그램 디버그: <F5> 키 또는 [디버그] > [디버깅 시작] 메뉴

// 시작을 위한 팁: 
//   1. [솔루션 탐색기] 창을 사용하여 파일을 추가/관리합니다.
//   2. [팀 탐색기] 창을 사용하여 소스 제어에 연결합니다.
//   3. [출력] 창을 사용하여 빌드 출력 및 기타 메시지를 확인합니다.
//   4. [오류 목록] 창을 사용하여 오류를 봅니다.
//   5. [프로젝트] > [새 항목 추가]로 이동하여 새 코드 파일을 만들거나, [프로젝트] > [기존 항목 추가]로 이동하여 기존 코드 파일을 프로젝트에 추가합니다.
//   6. 나중에 이 프로젝트를 다시 열려면 [파일] > [열기] > [프로젝트]로 이동하고 .sln 파일을 선택합니다.
