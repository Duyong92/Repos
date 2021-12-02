#pragma once

#include <iostream>
#include <string>

template <typename T>
T max(T& a, T& b) {
	//a 가 크면 a, b 가 크면 b
	return a > b ? a : b;
}

void run() {
	int a = 1, b = 2;
	//인스턴스화 되어 자동으로 int 타입으로 처리되었다.
	std::cout << "Max (" << a << "," << b << ") ? : " << max(a, b) << std::endl;

	std::string s = "hello", t = "world";
	std::cout << "Max (" << s << "," << t << ") ? : " << max(s, t) << std::endl;
}