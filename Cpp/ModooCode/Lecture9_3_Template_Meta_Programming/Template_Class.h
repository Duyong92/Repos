#pragma once
#include <iostream>
#include <typeinfo>

template <int N>
struct Int {
	static const int num = N;
};

template <typename T, typename U>
struct add {
	//T �� num�� U �� num�� �ҷ� ��������� ó���Ѵ�.
	typedef Int<T::num + U::num> result;
};

void run() {
	typedef Int<1> one;	//one �� num�� int 1�� ����.
	typedef Int<2> two;

	typedef add<one, two>::result three;

	std::cout << "Addtion result : " << three::num << std::endl;
}