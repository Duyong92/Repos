#pragma once

#include <vector>
using std::vector;

// [ Project Name ]Dlg.h

// DBF 파일 저장에 필요한 class 2개
class Field {
public:
	Field();
	~Field();

	// 기록창의 데이터 타입으로 아스키 코드 값을 enum 으로 관리
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
	//vector<string> _vField;		- 여러 시도를 해본 결과 char*로 사용하게 되었다고 한다.
	//vector<CString> _vField;
};

// dbf 파일 정보 불러오는 함수 및 저장 변수 클래스
class DBF {

};