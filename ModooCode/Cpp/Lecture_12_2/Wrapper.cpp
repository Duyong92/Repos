#pragma once
#include "Header_12_2.h"
#ifdef WRAPPER
#include <iostream>
#include <vector>
/* wraooer �� ���� �⺻ ����
template <typename T>
// wrapper(A()) �� ����� T& u �� ���ڷ� ������ �̻� ����.
void wrapper(T u) {
	g(u);
}
class A {};
void g(A& a) { std::cout << "������ ���۷��� ȣ��" << std::endl; }
void g(const A& a) { std::cout << "������ ��� ���۷��� ȣ��" << std::endl; }
void g(A&& a) { std::cout << "������ ���۷��� ȣ��" << std::endl; }
void Wrapper() {
	A a;
	const A ca;
	std::cout << "���� --------" << std::endl;
	g(a);
	g(ca);
// �� ������ ���۷����� ȣ��Ǵ°���? �������� ���µ�?
	g(A());
	std::cout << "Wrapper -----" << std::endl;
	wrapper(a);
	wrapper(ca);
	wrapper(A());
}*/
// const A& �� A& �� ���� ������ִ� ���
template <typename T>
void wrapper(T& u) {
	std::cout << "T& �� �߷е�" << std::endl;
	g(u);
}

template <typename T>
void wrapper(const T& u) {
	std::cout << "const T& �� �߷е�" << std::endl;
	g(u);
}

class A {};

void g(A& a) { std::cout << "������ ���۷��� ȣ��" << std::endl; }
void g(const A& a) { std::cout << "������ ��� ���۷��� ȣ��" << std::endl; }
void g(A&& a) { std::cout << "������ ���۷��� ȣ��" << std::endl; }

void Wrapper() {
	A a;
	const A ca;

	std::cout << "���� --------" << std::endl;
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

