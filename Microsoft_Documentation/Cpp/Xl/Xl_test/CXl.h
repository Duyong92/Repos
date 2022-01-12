/*
hpp ���Ϸ� �ۼ� ��, Visual Studio���� XML ���� �� ����� ������ ���� h ���Ϸ� ��ȯ�Ͽ����ϴ�.
*/
#include <ole2.h>
#include <comdef.h>

class CXl {
private:
	HRESULT m_hrCOMInit;						// COM �ʱ�ȭ ����
	HRESULT m_hrInit = ERROR_INVALID_VARIANT;	// Excel �ʱ�ȭ ����

	struct PROPERTIES {
		IDispatch* pXlApp;		// Excel
		IDispatch* pXlBooks;	// Main Frame
		IDispatch* pXlBook;		// Work Book
		IDispatch* pXlSheet;	// Sheet
	} m_XlProp;

public:
	/// <summary>
	///  Excel �ʱ�ȭ ���¿��� Excel�� ����ȭ �մϴ�.
	/// </summary>
	/// <param name="bVisible">: ����ȭ ����</param>
	///<returns>
	///���������� Excel�� ����ȭ ���� ���, 1�� ��ȯ�մϴ�.
	///Variant �ʱ�ȭ�� ���� �ʾ��� ��� -1�� ��ȯ�մϴ�.
	///Visible ��ȯ�� ���� ���� ��� -2�� ��ȯ�մϴ�.
	///</returns>
	int SetVisible(bool bVisible);

	int Open();

	//<summary>
	/// CLSID, Excel �ʱ�ȭ ���¿��� ������ ���ϴ�.
	///</summary>
	///<param name="file">: ���ϸ�</param>
	///<returns>
	/// ���� ���⸦ ������ ���, 1�� ��ȯ�մϴ�.<para/>
	/// CLSID, Excel �ʱ�ȭ�� �� �Ǿ��ų�, ���� ������ ���� ���, -1�� ��ȯ�մϴ�.
	///</returns>
	//int Open(const char* pszFile);

	/// <summary>
	/// Sheet�� ���ϴ�.
	/// </summary>
	/// <param name="nSheet"></param>
	/// <returns>Sheet�� ���������� ������ ���, 1�� ��ȯ�մϴ�.</returns>
	int SetActiveSheet(int nSheet);
	/// <summary>
	/// Sheet�� ���ϴ�.
	/// </summary>
	/// <param name="strSheet"></param>
	/// <returns>Sheet�� ���������� ������ ���, 1�� ��ȯ�մϴ�.</returns>
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
	/// �۾��� ������ �����մϴ�.
	/// </summary>
	void Save();
	
	/// <summary>
	/// Excel�� �����մϴ�.
	/// </summary>
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

bool CheckError(HRESULT hr);