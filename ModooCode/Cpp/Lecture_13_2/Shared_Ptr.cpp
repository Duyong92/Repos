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
        std::cout << "�ڿ��� ȹ����!" << std::endl;
    }

    ~A() {
        std::cout << "�Ҹ��� ȣ��!" << std::endl;
        delete[] data;
    }
};

void Shared_Ptr() {
    std::vector<std::shared_ptr<A>> vec;

    vec.push_back(std::shared_ptr<A>(new A()));
    vec.push_back(std::shared_ptr<A>(vec[0]));
    vec.push_back(std::shared_ptr<A>(vec[1]));

    // ������ ù��° ���Ҹ� �Ҹ� ��Ų��.
    std::cout << "ù ��° �Ҹ�!" << std::endl;
    vec.erase(vec.begin());

    // �� ���� ���Ҹ� �Ҹ� ��Ų��.
    std::cout << "���� ���� �Ҹ�!" << std::endl;
    vec.erase(vec.begin());

    // ������ ���� �Ҹ�
    std::cout << "������ ���� �Ҹ�!" << std::endl;
    vec.erase(vec.begin());

    std::shared_ptr<A> p1(new A()); // �ڿ��� ȹ����!
    std::shared_ptr<A> p2(p1);  // p2 ���� ������ ��ü A �� ����Ų��.

    std::cout << p1.use_count() << std::endl;  // 2
    std::cout << p2.use_count() << std::endl;  // 2
    
    std::shared_ptr<A> p3(p2);
    std::cout << p3.use_count() << std::endl;  // �� 3�� �ɱ�?
    std::cout << p1.use_count() << std::endl;   // �ٽ� ȣ���ϸ� 3�� �ȴ�.

    std::cout << "���α׷� ����!" << std::endl;
}
#endif // SHAERED_PTR
#ifndef SHAERED_PTR
void Shared_Ptr() {}
#endif // !SHAERED_PTR
