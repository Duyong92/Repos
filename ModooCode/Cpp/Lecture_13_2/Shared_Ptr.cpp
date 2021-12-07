#pragma once
#include "Header_13_2.h"
#ifdef SHAERED_PTR
#include <iostream>
#include <memory>
#include <vector>

class A {
    int* data;

public:
    A() {
        data = new int[100];
        std::cout << "자원을 획득함!" << std::endl;
    }

    ~A() {
        std::cout << "소멸자 호출!" << std::endl;
        delete[] data;
    }
};

void Shared_Ptr() {
    std::vector<std::shared_ptr<A>> vec;

    vec.push_back(std::shared_ptr<A>(new A()));
    vec.push_back(std::shared_ptr<A>(vec[0]));
    vec.push_back(std::shared_ptr<A>(vec[1]));

    // 벡터의 첫번째 원소를 소멸 시킨다.
    std::cout << "첫 번째 소멸!" << std::endl;
    vec.erase(vec.begin());

    // 그 다음 원소를 소멸 시킨다.
    std::cout << "다음 원소 소멸!" << std::endl;
    vec.erase(vec.begin());

    // 마지막 원소 소멸
    std::cout << "마지막 원소 소멸!" << std::endl;
    vec.erase(vec.begin());

    std::shared_ptr<A> p1(new A()); // 자원을 획득함!
    std::shared_ptr<A> p2(p1);  // p2 역시 생성된 객체 A 를 가리킨다.

    std::cout << p1.use_count() << std::endl;  // 2
    std::cout << p2.use_count() << std::endl;  // 2
    
    std::shared_ptr<A> p3(p2);
    std::cout << p3.use_count() << std::endl;  // 왜 3이 될까?
    std::cout << p1.use_count() << std::endl;   // 다시 호출하면 3이 된다.

    std::cout << "프로그램 종료!" << std::endl;
}
#endif // SHAERED_PTR
#ifndef SHAERED_PTR
void Shared_Ptr() {}
#endif // !SHAERED_PTR
