#pragma once
#include "Header_13_1.h"
#ifdef UNIQUE_PTR_VECTOR
#include <iostream>
#include <memory>
#include <vector>

class A {
    int* data;

public:
    A(int i) {
        std::cout << "자원을 획득함!" << std::endl;
        data = new int[100];
        data[0] = i;
    }

    void some() 
    { 
        //std::cout << "일반 포인터와 동일하게 사용가능!" << std::endl; 
        std::cout << "값 : " << data[0] << std::endl;
    }

    ~A() {
        std::cout << "자원을 해제함!" << std::endl;
        delete[] data;
    }
};

void Unique_Ptr_Vector() {
    std::vector<std::unique_ptr<A>> vec;
    /*
    std::unique_ptr<A> pa(new A(1));
    vec.push_back(pa);  // ??
    vec.push_back(std::move(pa)); // 잘 실행된다.
    */
    vec.emplace_back(new A(1));

    vec.back()->some();
}
#endif // UNIQUE_PTR_VECTOR
#ifndef UNIQUE_PTR_VECTOR
void Unique_Ptr_Vector() {}
#endif // !UNIQUE_PTR_VECTOR
