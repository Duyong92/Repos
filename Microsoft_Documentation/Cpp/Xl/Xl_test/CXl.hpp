#include <ole2.h>
#include <comdef.h>

class CXl {
private:
	HRESULT m_hrCOMInit;							// COM 초기화 여부
	HRESULT m_hrInit = ERROR_INVALID_VARIANT;	// Excel 초기화 여부

	struct PROPERTIES {
		IDispatch* pXlApp;		// Excel
		IDispatch* pXlBooks;	// Main Frame
		IDispatch* pXlBook;		// Work Book
		IDispatch* pXlSheet;	// Sheet
	} m_XlProp;

public:
	/// <summary>
	/// Excel을 가시화 합니다.
	/// </summary>
	/// <param name="bVisible">: 가시화 여부</param>
	/// <returns>
	/// 성공적으로 Excel을 가시화 했을 경우, 1을 반환합니다.
	/// <para/>Variant 초기화가 되지 않았을 경우 -1을 반환합니다.
	/// <para/>Visible 변환을 실패 했을 경우 -2를 반환합니다.
	/// </returns>
	int SetVisible(bool bVisible);

	/// <summary>
	/// Excel 파일을 엽니다.
	/// </summary>
	/// <param name="_file">: 파일명</param>
	/// <returns>
	/// <para/>파일 열기를 성공 시, 1을 반환합니다.
	/// <para/>파일 열기를 실패 시, 음수를 반환합니다.
	/// </returns>
	int Open(const char* _file);

	/**
	* @brief set active sheet to read and to write
	*/
	int SetActiveSheet(int nSheet);
	int SetActiveSheet(BSTR strSheet);
	/**
	 * @brief               get cell data on current active sheet
	 * @param[in]   pPos (char*)    cell position e.g. B4
	 * @param[out]  pData (char*)   cell data. string
	 */
	bool GetData(char* pPos, char* pData);
	bool GetData(char* pRow, int nCol, char* pData);

	/**
	 * @brief               set cell data on current active sheet
	 * @param[in]   pPos (char*)    cell position e.g. B4
	 * @param[in]   pData (char*)   cell data. string
	 */
	bool SetData(char* pPos, char* pData);
	/**
	 * @brief save workbook
	 */
	void Save();
	/**
	 * @brief close workbook
	 */
	void Close();

protected:
	/// <summary>
	/// CLSID를 선언하고, VARIANT를 초기화하여 Main Frame을 생성합니다.
	/// </summary>
	/// <returns>
	/// CLSID를 선언하지 못했을 경우, 에러 메시지와 -1을 반환합니다.
	/// <para/>인스턴스를 선언하지 못했을 경우, 에러 메시지와 -2를 반환합니다.
	/// <para/>성공적으로 Main Frame을 생성할 경우, 1을 반환합니다.
	/// </returns>
	int Init();
	
	// Excel 초기화 상태를 반환합니다.
	HRESULT CheckXlInit() { return m_hrInit; };	

public:
	// CXl 클래스 생성자입니다. COM 초기화 상태를 변경합니다.
	CXl();				

	// CXl 클래스 파괴자입니다.
	virtual ~CXl();		
};

HRESULT AutoWrap(int autoType, VARIANT* pvResult, IDispatch* pDisp, LPOLESTR ptName, int cArgs...);

bool CheckError(HRESULT _hr) {
	if (SUCCEEDED(_hr))
		return true;
	_com_error err(_hr);
	LPCTSTR errMsg = err.ErrorMessage();
	return false;
}