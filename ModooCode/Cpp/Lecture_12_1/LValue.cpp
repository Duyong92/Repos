#pragma once
#include "Header_12_1.h"
#ifdef LVALUE
#include <iostream>

int& func1(int& a) { return a; }
int func2(int b) { return b; }

void LValue() {
	int a = 3;
	func1(a) = 4;
	std::cout << &func1(a) << std::endl;

	int b = 2;
	a = func2(b);               // 가능
	func2(b) = 5;               // 오류 1
	std::cout << &func2(b) << std::endl;  // 오류 2
}
#endif
#ifndef LVALUE
void LValue() {}
#endif