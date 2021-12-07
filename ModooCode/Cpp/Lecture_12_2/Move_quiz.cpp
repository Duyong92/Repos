#pragma once
#include "Header_12_2.h"
#ifdef MOVE_QUIZ
#include <iostream>
class A {
public:
	A() { std::cout << "ctor\n"; }
	A(const A& a) { std::cout << "copy ctor\n"; }
	A(A&& a) { std::cout << "move ctor\n"; }
};

/* �״�� a �� �޴´�.

class B {
public:
	B(const A& a) : a_(a) {}
	A a_;
};
void Move_quiz() {
	A a;
	std::cout << "create B-- \n";
	B b(a);
}*/

/* move(a) �� ���� �̵����ѷ��� �Ѵ�.

class B {
public:
	B(const A& a) : a_(std::move(a)) {}
	A a_;
};
void Move_quiz() {
	A a;
	std::cout << "create B-- \n";
	B b(a);
}*/

/* move(a) �� ���� ���������� A&& �� �ް� �Ѵ�.

class B {
public:
	B(A&& a) : a_(a) {}
	A a_;
};

void Move_quiz() {
	A a;
	std::cout << "create B-- \n";
	B b(std::move(a));
}*/

// ����
class B {
public:
	B(A&& a) : a_(std::move(a)) {}
	A a_;
};

void Move_quiz() {
	A a;
	std::cout << "create B-- \n";
	B b(std::move(a));
}
#endif // MOVE_QUIZ
#ifndef MOVE_QUIZ
void Move_quiz() {}
#endif // !MOVE_QUIZ
