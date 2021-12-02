#pragma once

#include <iostream>
#include <string>

template <typename T>
T max(T& a, T& b) {
	//a �� ũ�� a, b �� ũ�� b
	return a > b ? a : b;
}

void run() {
	int a = 1, b = 2;
	//�ν��Ͻ�ȭ �Ǿ� �ڵ����� int Ÿ������ ó���Ǿ���.
	std::cout << "Max (" << a << "," << b << ") ? : " << max(a, b) << std::endl;

	std::string s = "hello", t = "world";
	std::cout << "Max (" << s << "," << t << ") ? : " << max(s, t) << std::endl;
}