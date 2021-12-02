#pragma once

#include <iostream>
#include <string>

//���ø� ���ڸ� �������� �ʴ´ٸ� ������ ������ �߻��Ѵ�.
template <typename T, int num>
T add_num(T t) {
	return t + num;
}

//���⼭���ʹ� �׽�Ʈ�̴�.
template<typename U, typename V>
std::string add_string(U& u, V& v) {
	return u + v;
}

void run() {
	int x = 3;
	std::cout << "x : " << add_num<int, 5>(x) << std::endl;

	//���⼭���ʹ� �׽�Ʈ ��ºκ��̴�.
	std::string s = "�׽�Ʈ ��";
	char c = 'a';
	std::cout << "s + c : " << add_string<std::string, char>(s, c) << std::endl;
	char* cP = (char*)("hello");
	std::string s2 = " world";
	std::cout << "cP + s2 : " << add_string<char*, std::string>(cP, s2) << std::endl;
}