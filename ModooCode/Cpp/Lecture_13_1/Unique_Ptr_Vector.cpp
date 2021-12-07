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
        std::cout << "�ڿ��� ȹ����!" << std::endl;
        data = new int[100];
        data[0] = i;
    }

    void some() 
    { 
        //std::cout << "�Ϲ� �����Ϳ� �����ϰ� ��밡��!" << std::endl; 
        std::cout << "�� : " << data[0] << std::endl;
    }

    ~A() {
        std::cout << "�ڿ��� ������!" << std::endl;
        delete[] data;
    }
};

void Unique_Ptr_Vector() {
    std::vector<std::unique_ptr<A>> vec;
    /*
    std::unique_ptr<A> pa(new A(1));
    vec.push_back(pa);  // ??
    vec.push_back(std::move(pa)); // �� ����ȴ�.
    */
    vec.emplace_back(new A(1));

    vec.back()->some();
}
#endif // UNIQUE_PTR_VECTOR
#ifndef UNIQUE_PTR_VECTOR
void Unique_Ptr_Vector() {}
#endif // !UNIQUE_PTR_VECTOR
