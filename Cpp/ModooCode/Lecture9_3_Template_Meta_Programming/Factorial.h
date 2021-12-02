#pragma once
/* ������ Ÿ�� ���丮�� ��� */
#include <iostream>
template <int N>
struct Factorial {
	static const int result = N * Factorial<N - 1>::result;
};
//result = 6 * Factorial<6 - 1>
//result = 6 * 5 * Factorial<5 - 1>
//result = 6 * 5 * ... * Factorial< 1 >
//result = 6 * 5 * ... * 1

//���ø� Ư��ȭ
//Ư��ȭ�� ���� loop(����Լ�)�� �����.
template <>
struct Factorial<1> {
	static const int result = 1;
};

void run() {
	std::cout << "6! = 1*2*3*4*5*6 = " << Factorial<6>::result << std::endl;
}