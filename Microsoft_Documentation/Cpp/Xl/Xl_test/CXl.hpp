#include <ole2.h>
#include <comdef.h>

class CXl {
private:
	HRESULT m_hrCOMInit;							// COM �ʱ�ȭ ����
	HRESULT m_hrInit = ERROR_INVALID_VARIANT;	// Excel �ʱ�ȭ ����

	struct PROPERTIES {
		IDispatch* pXlApp;		// Excel
		IDispatch* pXlBooks;	// Main Frame
		IDispatch* pXlBook;		// Work Book
		IDispatch* pXlSheet;	// Sheet
	} m_XlProp;

public:
	/// <summary>
	/// Excel�� ����ȭ �մϴ�.
	/// </summary>
	/// <param name="bVisible">: ����ȭ ����</param>
	/// <returns>
	/// ���������� Excel�� ����ȭ ���� ���, 1�� ��ȯ�մϴ�.
	/// <para/>Variant �ʱ�ȭ�� ���� �ʾ��� ��� -1�� ��ȯ�մϴ�.
	/// <para/>Visible ��ȯ�� ���� ���� ��� -2�� ��ȯ�մϴ�.
	/// </returns>
	int SetVisible(bool bVisible);

	/// <summary>
	/// Excel ������ ���ϴ�.
	/// </summary>
	/// <param name="_file">: ���ϸ�</param>
	/// <returns>
	/// <para/>���� ���⸦ ���� ��, 1�� ��ȯ�մϴ�.
	/// <para/>���� ���⸦ ���� ��, ������ ��ȯ�մϴ�.
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
	/// CLSID�� �����ϰ�, VARIANT�� �ʱ�ȭ�Ͽ� Main Frame�� �����մϴ�.
	/// </summary>
	/// <returns>
	/// CLSID�� �������� ������ ���, ���� �޽����� -1�� ��ȯ�մϴ�.
	/// <para/>�ν��Ͻ��� �������� ������ ���, ���� �޽����� -2�� ��ȯ�մϴ�.
	/// <para/>���������� Main Frame�� ������ ���, 1�� ��ȯ�մϴ�.
	/// </returns>
	int Init();
	
	// Excel �ʱ�ȭ ���¸� ��ȯ�մϴ�.
	HRESULT CheckXlInit() { return m_hrInit; };	

public:
	// CXl Ŭ���� �������Դϴ�. COM �ʱ�ȭ ���¸� �����մϴ�.
	CXl();				

	// CXl Ŭ���� �ı����Դϴ�.
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