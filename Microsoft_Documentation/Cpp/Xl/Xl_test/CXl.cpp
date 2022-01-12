#include "CXl.h"

bool CheckError(HRESULT hr)
{
    if (SUCCEEDED(hr))
        return true;
    _com_error err(hr);
    LPCTSTR errMsg = err.ErrorMessage();
    return false;
}

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
        sprintf_s(buf, "IDispatch::GetIDsOfNames(\"%s\") failed w/err 0x%08lx", szName, hr);
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
        sprintf_s(buf, "IDispatch::Invoke(\"%s\"=%08lx) failed w/err 0x%08lx", szName, dispID, hr);
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
    
    AutoWrap(DISPATCH_PROPERTYGET, &result, m_XlProp.pXlApp, (wchar_t*)L"Workbooks", 0);
    m_XlProp.pXlBooks = result.pdispVal;
    m_hrInit = S_OK;
    return 1;
}

int CXl::SetVisible(bool bVisible) {
    if (!CheckError(CheckXlInit())) 
        return -1;

    VARIANT x;
    x.vt = VT_I4;
    x.lVal = bVisible ? 1 : 0;
    if (CheckError(AutoWrap(DISPATCH_PROPERTYPUT, NULL, m_XlProp.pXlApp, (wchar_t*)L"Visible", 1, x)))
        return -1;

    return 1;
}

int CXl::Open() {
    if (Init() < 0)
        return -1;
    if (!CheckError(CheckXlInit()))
        return -1;

    SetVisible(true);

    return 1;
}

/*
int CXl::Open(const char* pszFile) {
    if (Init() < 0)
        return -1;
    if (!CheckError(CheckXlInit()))
        return -1;
        
    VARIANT result;
    VARIANT path;
    VariantInit(&result);
    
    if (pszFile == NULL) {
        ::MessageBoxA(NULL, "파일 정보가 없습니다.", "에러", 0x10010);
        return -1;
    }
    
    _bstr_t str = pszFile;
    path.vt = VT_BSTR;
    path.bstrVal = ::SysAllocString(str);
            
    AutoWrap(DISPATCH_METHOD, &result, m_XlProp.pXlBooks, (wchar_t*)L"Open", 1, path);
    m_XlProp.pXlBook = result.pdispVal;
    SysFreeString(path.bstrVal);
    
    return 1;
}
*/

int CXl::SetActiveSheet(int nSheet) {
    VARIANT result;
    VariantInit(&result);
    VARIANT sheet;
    sheet.vt = VT_I4;
    sheet.lVal = nSheet;

    AutoWrap(DISPATCH_PROPERTYGET, &result, m_XlProp.pXlApp, (wchar_t*)L"Worksheets", 1, sheet);
    m_XlProp.pXlSheet = result.pdispVal;

    return 1;
}

int CXl::SetActiveSheet(BSTR strSheet) {
    VARIANT result;
    VariantInit(&result);
    VARIANT sheet;
    sheet.vt = VT_BSTR;
    sheet.bstrVal = strSheet;

    AutoWrap(DISPATCH_PROPERTYGET, &result, m_XlProp.pXlApp, (wchar_t*)L"Worksheets", 1, sheet);
    m_XlProp.pXlSheet = result.pdispVal;

    return 1;
}

void CXl::Save() {
    AutoWrap(DISPATCH_METHOD, NULL, m_XlProp.pXlApp, (wchar_t*)L"Save", 0);
}

void CXl::Close() {
    AutoWrap(DISPATCH_METHOD, NULL, m_XlProp.pXlApp, (wchar_t*)L"Quit", 0);;
    m_XlProp.pXlSheet->Release();
    m_XlProp.pXlBook->Release();
    m_XlProp.pXlBooks->Release();
    m_XlProp.pXlApp->Release();
}