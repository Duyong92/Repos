#pragma once

#include <iostream>

template <typename T>
struct Compare {
	bool operator()(const T& a, const T& b) const { return a < b; }
};

template <typename T, typename Comp = Compare<T>>
T Min(T a, T b) {
	Comp comp;
	if (comp(a, b)) {
		return a;
	}
	return b;
}

template <typename T, int num = 5>
T add_num(T t) {
	return t + num;
}

void run() {
	int x = 3;
	std::cout << "x : " << add_num(x) << std::endl;
	std::cout << std::endl;

	int a = 3, b = 5;
	std::cout << "Min " << a << " , " << b << " :: " << Min(a, b) << std::endl;

	std::string s1 = "abc", s2 = "def";
	std::cout << "Min " << s1 << " , " << s2 << " :: " << Min(s1, s2)
		<< std::endl;
}