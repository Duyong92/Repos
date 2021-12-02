#pragma once
/* 컴파일 타임 팩토리얼 계산 */
#include <iostream>
template <int N>
struct Factorial {
	static const int result = N * Factorial<N - 1>::result;
};
//result = 6 * Factorial<6 - 1>
//result = 6 * 5 * Factorial<5 - 1>
//result = 6 * 5 * ... * Factorial< 1 >
//result = 6 * 5 * ... * 1

//템플릿 특수화
//특수화를 통해 loop(재귀함수)를 멈춘다.
template <>
struct Factorial<1> {
	static const int result = 1;
};

void run() {
	std::cout << "6! = 1*2*3*4*5*6 = " << Factorial<6>::result << std::endl;
}