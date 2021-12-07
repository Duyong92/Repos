#pragma once
#include "Header_13_1.h"
#ifdef UNIQUE_PTR_ADVANCED
#include <iostream>
#include <memory>

class A {
    int* data;

public:
    A() {
        std::cout << "자원을 획득함!" << std::endl;
        data = new int[100];
    }

    void some() { std::cout << "일반 포인터와 동일하게 사용가능!" << std::endl; }

    void do_sth(int a) {
        std::cout << "무언가를 한다!" << std::endl;
        data[0] = a;
    }

    ~A() {
        std::cout << "자원을 해제함!" << std::endl;
        delete[] data;
    }
};

class Foo {
    int a, b;

public:
    Foo(int a, int b) : a(a), b(b) { std::cout << "생성자 호출!" << std::endl; }
    void print() { std::cout << "a : " << a << ", b : " << b << std::endl; }
    ~Foo() { std::cout << "소멸자 호출!" << std::endl; }
};

// 올바르지 않은 전달 방식
//void do_something(std::unique_ptr<A>& ptr) { ptr->do_sth(3); }
void do_something(A* ptr) { ptr->do_sth(3); }

void Unique_Ptr_advanced() {
    std::unique_ptr<A> pa(new A());
    //do_something(pa);
    do_something(pa.get());

    auto ptr = std::make_unique<Foo>(3, 5);
    ptr->print();
}
#endif // UNIQUE_PTR_ADVANCED
#ifndef UNIQUE_PTR_ADVANCED
void Unique_Ptr_advanced() {}
#endif // !UNIQUE_PTR_ADVANCED
