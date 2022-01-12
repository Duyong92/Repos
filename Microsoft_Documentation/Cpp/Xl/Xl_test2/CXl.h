#include <ole2.h>
#include <iostream>

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

	int AddWorkBook();

	int AddActiveSheet();

	//XFD1048576 �� �ִ����� �޸� ���ҽ� �������� ���� ���� 5000 ������ �����մϴ�.
	//default�� ���� ���� ��� clock() �������� 628.000 ms ���� �ҿ�˴ϴ�.
	int SetRange(const char* pcszStart = "A1", const char* pcszEnd = "EFD05000");

	int SetSafeBound(VARIANT& va, unsigned int unYMin = 1, unsigned int unYMax = 100, unsigned int unXMin = 1, unsigned int unXMax = 100);

	int SetData(VARIANT vaArray, VARIANT vaData, unsigned int unRow, unsigned int unColumn);

	int Print(VARIANT vaArray);

	int SetActiveSheet(int nSheet);

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