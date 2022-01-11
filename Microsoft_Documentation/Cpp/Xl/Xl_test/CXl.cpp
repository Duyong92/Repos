#include "CXl.hpp"

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

CXl::CXl() {
    CheckError(m_hrCOMInit = CoInitialize(NULL));
}

CXl::~CXl() {
    if (m_hrCOMInit == S_OK)
        CoUninitialize();
}

int CXl::Init() {
    CLSID clsid;
    if (CheckError(CLSIDFromProgID(L"Excel.Application", &clsid)))
        return -1;
    if (CheckError(CoCreateInstance(clsid, NULL, CLSCTX_LOCAL_SERVER, IID_IDispatch, (void**)&m_XlProp.pXlApp)))
        return -2;

    VARIANT result;
    VariantInit(&result);
    // 이쪽부터 수정해야 합니다. f-1
    AutoWrap(DISPATCH_PROPERTYGET, &result, m_XlProp.pXlApp, (wchar_t*)L"Workbooks", 0);
    m_XlProp.pXlBooks = result.pdispVal;
    m_hrInit = S_OK;
    return 1;
}

int CXl::SetVisible(bool bVisible) {
    // Variant 부분이 조금 많이 어색합니다. f-1
    if (!CheckError(CheckXlInit())) 
        return -1;

    VARIANT x;
    x.vt = VT_I4;
    x.lVal = bVisible ? 1 : 0;
    if (CheckError(AutoWrap(DISPATCH_PROPERTYPUT, NULL, m_XlProp.pXlApp, (wchar_t*)L"Visible", 1, x)))
        return -1;

    return 1;
}

int CXl::Open(const char* _file) {
    if (Init() < 0)
        return -1;
    if (!CheckError(CheckXlInit()))
        return -1;
    // 메시지 부분 통일 필요합니다.
    if (_file == NULL) {
        ::MessageBoxA(NULL, "파일 정보가 없습니다.", "에러", 0x10010);
    }
        

}