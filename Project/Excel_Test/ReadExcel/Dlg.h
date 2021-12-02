#pragma once

#include <vector>
using std::vector;

// [ Project Name ]Dlg.h

// DBF ���� ���忡 �ʿ��� class 2��
class Field {
public:
	Field();
	~Field();

	// ���â�� ������ Ÿ������ �ƽ�Ű �ڵ� ���� enum ���� ����
	/*
	B: binary, a string
	C: Charactre
	D: Date
	L: Logical
	M: Memo
	N: Numeric
	*/
	enum _eRecordItemDataType {B,C,D,L,M,N};

	// member varioius
	char _cTitle[11];
	char _cDataType;
	unsigned char _ucFieldLength;
	char _cFieldContent[100];
	vector<bool> compareExist;
	vector<char*> _vField;
	//vector<string> _vField;		- ���� �õ��� �غ� ��� char*�� ����ϰ� �Ǿ��ٰ� �Ѵ�.
	//vector<CString> _vField;
};

// dbf ���� ���� �ҷ����� �Լ� �� ���� ���� Ŭ����
class DBF {

};