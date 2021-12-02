#pragma once
#include <iostream>
#include <typeinfo>

template <int N>
struct Int {
	static const int num = N;
};

template <typename T, typename U>
struct add {
	//T 의 num과 U 의 num을 불러 산술연산을 처리한다.
	typedef Int<T::num + U::num> result;
};

void run() {
	typedef Int<1> one;	//one 의 num에 int 1이 들어간다.
	typedef Int<2> two;

	typedef add<one, two>::result three;

	std::cout << "Addtion result : " << three::num << std::endl;
}