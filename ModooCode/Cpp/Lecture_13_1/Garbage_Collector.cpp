#pragma once
#include "Header_13_1.h"
#ifdef GARBAGE_COLLECTOR
#include <iostream>

class A {
    int* data;

public:
    A() {
        data = new int[100];
        std::cout << "�ڿ��� ȹ����!" << std::endl;
    }

    ~A() {
        std::cout << "�ڿ��� ������!" << std::endl;
        delete[] data;
    }
};

void thrower() {
    // ���ܸ� �߻���Ŵ!
    throw 1;
}

void do_something() {
    A* pa = new A();
    thrower();

    // �߻��� ���ܷ� ���� delete pa �� ȣ����� �ʴ´�!
    delete pa;
}

void Garbage_Collector() 
{
    //do_something();
    // �Ҵ�� ��ü�� �Ҹ���� ����!
    // ��, 400 ����Ʈ (4 * 100) ��ŭ�� �޸� ���� �߻�
    try {
        do_something();
    }
    catch (int i) {
        std::cout << "���� �߻�!" << std::endl;
        // ���� ó��
    }
}
#endif // GARBAGE_COLLECTOR
#ifndef GARBAGE_COLLECTOR
void Garbage_Collector() {}
#endif // !GARBAGE_COLLECTOR
