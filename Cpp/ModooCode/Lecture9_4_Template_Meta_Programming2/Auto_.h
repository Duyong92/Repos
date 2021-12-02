#pragma once
#include <iostream>
#include <typeinfo>

int sum(int a, int b) { return a + b; }

class SomeClass {
	int data;

public:
	SomeClass(int d) : data(d) {}
	SomeClass(const SomeClass& s) : data(s.data) {}
};

void run() {
	auto c = sum(1, 2);  // �Լ� ���� Ÿ������ ���� int ��� ���� ����
	auto num = 1.0 + 2.0;  // double �� ���� ����!

	SomeClass some(10);
	auto some2 = some;

	auto some3(10);  // SomeClass ��ü�� ������?

	std::cout << "c �� Ÿ����? :: " << typeid(c).name() << std::endl;
	std::cout << "num �� Ÿ����? :: " << typeid(num).name() << std::endl;
	std::cout << "some2 �� Ÿ����? :: " << typeid(some2).name() << std::endl;
	std::cout << "some3 �� Ÿ����? :: " << typeid(some3).name() << std::endl;
}