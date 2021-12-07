#pragma once
#include "Header_12_2.h"
#ifdef MOVE_SEMANTICS
#include <iostream>
#include <utility>

class A {
public:
	A() { std::cout << "일반 생성자 호출!" << std::endl; }
	A(const A& a) { std::cout << "복사 생성자 호출!" << std::endl; }
	A(A&& a) { std::cout << "이동 생성자 호출!" << std::endl; }
};

void Move_Semantics() {
	A a;

	std::cout << "---------" << std::endl;
	A b(a);

	std::cout << "---------" << std::endl;
	A c(std::move(a));
}
#endif	// MOVE_SEMANTICS
#ifndef MOVE_SEMANTICS
void Move_Semantics() {}
#endif	// MOVE_SEMANTICS

