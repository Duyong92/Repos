/*
hpp 파일로 작성 시, Visual Studio에서 XML 읽을 때 생기는 오류로 인해 h 파일로 변환하였습니다.
*/
#include <ole2.h>
#include <comdef.h>

class CXl {
private:
	HRESULT m_hrCOMInit;						// COM 초기화 여부
	HRESULT m_hrInit = ERROR_INVALID_VARIANT;	// Excel 초기화 여부

	struct PROPERTIES {
		IDispatch* pXlApp;		// Excel
		IDispatch* pXlBooks;	// Main Frame
		IDispatch* pXlBook;		// Work Book
		IDispatch* pXlSheet;	// Sheet
	} m_XlProp;

public:
	/// <summary>
	///  Excel 초기화 상태에서 Excel을 가시화 합니다.
	/// </summary>
	/// <param name="bVisible">: 가시화 여부</param>
	///<returns>
	///성공적으로 Excel을 가시화 했을 경우, 1을 반환합니다.
	///Variant 초기화가 되지 않았을 경우 -1을 반환합니다.
	///Visible 변환을 실패 했을 경우 -2를 반환합니다.
	///</returns>
	int SetVisible(bool bVisible);

	int Open();

	//<summary>
	/// CLSID, Excel 초기화 상태에서 파일을 엽니다.
	///</summary>
	///<param name="file">: 파일명</param>
	///<returns>
	/// 파일 열기를 성공할 경우, 1을 반환합니다.<para/>
	/// CLSID, Excel 초기화가 안 되었거나, 파일 정보가 없을 경우, -1를 반환합니다.
	///</returns>
	//int Open(const char* pszFile);

	/// <summary>
	/// Sheet를 엽니다.
	/// </summary>
	/// <param name="nSheet"></param>
	/// <returns>Sheet를 성공적으로 열었을 경우, 1을 반환합니다.</returns>
	int SetActiveSheet(int nSheet);
	/// <summary>
	/// Sheet를 엽니다.
	/// </summary>
	/// <param name="strSheet"></param>
	/// <returns>Sheet를 성공적으로 열었을 경우, 1을 반환합니다.</returns>
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
	/// <summary>
	/// 작업한 내용을 저장합니다.
	/// </summary>
	void Save();
	
	/// <summary>
	/// Excel을 종료합니다.
	/// </summary>
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

bool CheckError(HRESULT hr);