#pragma warning(disable:4996)
// Xl.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <ole2.h> // OLE2 Definitions

wchar_t* pbzPSZ(const char* _pbz) {
    wchar_t* psz;

    int n = MultiByteToWideChar(CP_ACP, 0, _pbz, -1, NULL, NULL);

    psz = new WCHAR[n];

    MultiByteToWideChar(CP_ACP, 0, _pbz, strlen(_pbz) + 1, psz, n);

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
    /// <summary> 
    /// 스레드에서 COM 라이브러리를 최기화하여 표준 할당자와 메모리 할당 함수에 대한 포인터를 가져옵니다.
    /// </summary>
    /// <result>
    /// 스레드에서 COM 라이브러리를 성공적으로 초기화하였다면 S_OK를 반환합니다.
    /// 스레드에서 이미 초기화가 되어 있는 경우 S_FALSE를 반환합니다.
    /// 다중 스레드로 초기화 후 호출을 실패한다면 RPC_E_CHANGED_MODE를 반환합니다.
    /// </result>
    HRESULT hr = CoInitialize(NULL);

    if (FAILED(hr))
    {
        ::MessageBoxA(NULL, "Colntialize() failed", "Error", 0x10010);
        return -1;
    }

    // CLSID를 서버로 가져옵니다.
    CLSID clsid;
    
    /// <summary>
    /// ProgID가 주어지면 CLSIDFromProgID는 레지스트리에서 연결된 CLSID를 찾습니다.
    /// </summary>
    /// <param=lpszProgID>: CLSID가 요구한 ProgID 포인터</param>
    /// <param=lpclsid>: 회수된 CLSID 반환값의 포인터</param>
    /// <returns>
    /// CLSID를 성공적으로 회수하면 S_OK를 반환합니다.
    /// <para/>ProgID가 유효하지 않을 경우 CO_E_CLASSSTRING을 반환합니다.
    /// <para/>CLSID를 기재하는데 오류가 발생할 경우 REGDB_EWRITERGDB를 반환합니다.
    /// </returns>
    hr = CLSIDFromProgID(L"Excel.Application", &clsid);

    if (FAILED(hr))
    {
        ::MessageBoxA(NULL, "CLSIDFromProgID() failed", "Error", 0x10010);
        return -2;
    }

    // Start server and get IDispatch...
    IDispatch* pXlApp;
    /// <summary>
    /// 지정된 CLSID와 연결된 클래스의 단일 개체를 만들고 기본 초기화합니다.
    /// </summary>
    /// <param=rclsid>: object를 생성하기 위해 데이터와 코드를 연관된 CLSID</param>
    /// <param=pUnkOuter>: 집계 개체의 IUnknown 인터페이스에 대한 포인터<para/>
    /// (NULL일 경우, 집약관계에 object가 해당되지 않는다.)</param>
    /// <param=dwClsContext>: 새로 생성 개체를 관리하는 코드가 실행되는 Context</param>
    /// <param=riid>: 개체와 통신하는 데 사용할 인터페이스의 식별자에 대한 참조</param>
    /// <param=*ppv>: riid에서 요청한 인터페이스 포인터를 받는 포인터 변수의 주소</param>
    /// <returns>
    /// 지정된 개체 클래스의 인스턴스가 성공적으로 생성되었을 경우, S_OK를 반환합니다.
    /// <para/>지정된 클래스가 등록 데이터베이스에 등록되어 있지 않을 경우, REGDB_E_CLASSNOTREG를 반환합니다.
    /// <para/>집계의 일부로 만들 수 없는 경우, CLASS_E_NOAGGREGATION을 반환합니다.
    /// <para/>지정된 클래스가 요청된 인터페이스를 구현하지 않거나 제어하는 ​​IUnknown이 요청된 인터페이스를 노출
    /// <para/>되지 않을 경우, E_NOINTERFACE를 반환합니다.
    /// <para/>ppv 파라미터가 NULL일 경우, E_POINTER를 반환합니다.
    /// </returns>
    hr = CoCreateInstance(clsid, NULL, CLSCTX_LOCAL_SERVER, IID_IDispatch, (void**)&pXlApp);
    if (FAILED(hr))
    {
        ::MessageBoxA(NULL, "Excel not registered properly", "Error", 0x10010);
        return -2;
    }
    
    // Make it visible (i.e. app.visible = 1)
    // Excel 창을 킵니다.
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
    // 새 Sheet를 킵니다.
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
        // SafeArrayCreate()가 무엇을 하는 함수인가요?
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
        parm.bstrVal = ::SysAllocString(L"A1:Q17");

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

    // Uninitialize COM for this thread...
    CoUninitialize();
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
