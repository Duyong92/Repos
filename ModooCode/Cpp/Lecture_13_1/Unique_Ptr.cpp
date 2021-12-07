#pragma once
#include "Header_13_1.h"
#ifdef UNIQUE_PTR
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

    ~A() {
        std::cout << "자원을 해제함!" << std::endl;
        delete[] data;
    }
};

void do_something() {
    std::unique_ptr<A> pa(new A());
    //pa->some();

    // pb 도 객체를 가리키게 할 수 있을까? 답은 없다.
    // std::unique_ptr<A> pb = pa;

    std::cout << "pa : ";
    pa->some();

    // pa 가 가리키고 있는 실제 주소값을 확인해보면 nullptr 이 나온다.
    // pb 에 소유권을 이전.
    std::unique_ptr<A> pb = std::move(pa);
    std::cout << "pb : ";
    pb->some();

    // 되는데?
    std::cout << "pa : ";
    pa->some();
    std::cout << "pa : " << pa.get() << std::endl;
}

void Unique_Ptr() { do_something(); }
#endif // UNIQUE_PTR
#ifndef UNIQUE_PTR
void Unique_Ptr() {}
#endif // !UNIQUE_PTR
