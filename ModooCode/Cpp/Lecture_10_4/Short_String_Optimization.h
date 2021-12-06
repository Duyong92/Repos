#pragma once
#include <iostream>
#include <string>

// 이와 같이 new 를 전역 함수로 정의하면 모든 new 연산자를 오버로딩 해버린다.
// (어떤 클래스의 멤버 함수로 정의하면 해당 클래스의 new 만 오버로딩됨)
void* operator new(std::size_t count) {
	std::cout << count << " bytes 할당 " << std::endl;
	return malloc(count);
}

void run() {
	std::cout << "s1 생성 --- " << std::endl;
	std::string s1 = "this is a pretty long sentence!!!";
	std::cout << "s1 크기 : " << sizeof(s1) << std::endl;

	std::cout << "s2 생성 --- " << std::endl;
	std::string s2 = "short sentence";
	std::cout << "s2 크기 : " << sizeof(s2) << std::endl;

	std::cout << std::endl << "문자열 뒤에 s를 추가하는 방법" << std::endl;
	using namespace std::literals;

	auto s3 = "hello"s;
	std::cout << "s3 길이 : " << s3.size() << std::endl;
	
	std::cout << std::endl;
	std::cout << std::endl << "그 외의 literal 정의 방법" << std::endl;
	std::wstring wstr = L"hello";
	std::cout << "wstr 길이 : " << wstr.size() << std::endl;

	std::cout << std::endl << "Raw string literal" << std::endl;
	std::string str = R"(asdfasdf
이 안에는
어떤 것들이 와도
// 이런것도 되고
#define hasldfjalskdfj
\n\n <--- Escape 안해도 됨
	)";
	std::cout << str << std::endl;

	std::cout << std::endl << "()도 넣는 방법" << std::endl;
	std::string str1 = R"foo(
)"; <-- 무시됨
)foo";

	std::cout << str1 << std::endl;
}