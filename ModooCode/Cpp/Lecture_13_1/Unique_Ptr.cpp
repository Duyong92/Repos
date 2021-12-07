#pragma once
#include "Header_13_1.h"
#ifdef UNIQUE_PTR
#include <iostream>
#include <memory>

class A {
    int* data;

public:
    A() {
        std::cout << "�ڿ��� ȹ����!" << std::endl;
        data = new int[100];
    }

    void some() { std::cout << "�Ϲ� �����Ϳ� �����ϰ� ��밡��!" << std::endl; }

    ~A() {
        std::cout << "�ڿ��� ������!" << std::endl;
        delete[] data;
    }
};

void do_something() {
    std::unique_ptr<A> pa(new A());
    //pa->some();

    // pb �� ��ü�� ����Ű�� �� �� ������? ���� ����.
    // std::unique_ptr<A> pb = pa;

    std::cout << "pa : ";
    pa->some();

    // pa �� ����Ű�� �ִ� ���� �ּҰ��� Ȯ���غ��� nullptr �� ���´�.
    // pb �� �������� ����.
    std::unique_ptr<A> pb = std::move(pa);
    std::cout << "pb : ";
    pb->some();

    // �Ǵµ�?
    std::cout << "pa : ";
    pa->some();
    std::cout << "pa : " << pa.get() << std::endl;
}

void Unique_Ptr() { do_something(); }
#endif // UNIQUE_PTR
#ifndef UNIQUE_PTR
void Unique_Ptr() {}
#endif // !UNIQUE_PTR
