#pragma once

#include <iostream>
#include <string>

//템플릿 인자를 지정하지 않는다면 컴파일 오류가 발생한다.
template <typename T, int num>
T add_num(T t) {
	return t + num;
}

//여기서부터는 테스트이다.
template<typename U, typename V>
std::string add_string(U& u, V& v) {
	return u + v;
}

void run() {
	int x = 3;
	std::cout << "x : " << add_num<int, 5>(x) << std::endl;

	//여기서부터는 테스트 출력부분이다.
	std::string s = "테스트 중";
	char c = 'a';
	std::cout << "s + c : " << add_string<std::string, char>(s, c) << std::endl;
	char* cP = (char*)("hello");
	std::string s2 = " world";
	std::cout << "cP + s2 : " << add_string<char*, std::string>(cP, s2) << std::endl;
}