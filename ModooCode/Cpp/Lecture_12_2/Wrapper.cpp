#pragma once
#include "Header_12_2.h"
#ifdef WRAPPER
#include <iostream>
#include <vector>
/* wraooer 에 대한 기본 이해
template <typename T>
// wrapper(A()) 를 숨기고 T& u 를 인자로 받으면 이상 없다.
void wrapper(T u) {
	g(u);
}
class A {};
void g(A& a) { std::cout << "좌측값 레퍼런스 호출" << std::endl; }
void g(const A& a) { std::cout << "좌측값 상수 레퍼런스 호출" << std::endl; }
void g(A&& a) { std::cout << "우측값 레퍼런스 호출" << std::endl; }
void Wrapper() {
	A a;
	const A ca;
	std::cout << "원본 --------" << std::endl;
	g(a);
	g(ca);
// 왜 우측값 레퍼런스가 호출되는거죠? 우측값이 없는데?
	g(A());
	std::cout << "Wrapper -----" << std::endl;
	wrapper(a);
	wrapper(ca);
	wrapper(A());
}*/
// const A& 와 A& 를 따로 만들어주는 방법
template <typename T>
void wrapper(T& u) {
	std::cout << "T& 로 추론됨" << std::endl;
	g(u);
}

template <typename T>
void wrapper(const T& u) {
	std::cout << "const T& 로 추론됨" << std::endl;
	g(u);
}

class A {};

void g(A& a) { std::cout << "좌측값 레퍼런스 호출" << std::endl; }
void g(const A& a) { std::cout << "좌측값 상수 레퍼런스 호출" << std::endl; }
void g(A&& a) { std::cout << "우측값 레퍼런스 호출" << std::endl; }

void Wrapper() {
	A a;
	const A ca;

	std::cout << "원본 --------" << std::endl;
	g(a);
	g(ca);
	g(A());

	std::cout << "Wrapper -----" << std::endl;
	wrapper(a);
	wrapper(ca);
	wrapper(A());
}
#endif // WRAPPER
#ifndef WRAPPER
void Wrapper() {}
#endif // !WRAPPER

