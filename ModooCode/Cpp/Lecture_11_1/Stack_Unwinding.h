#pragma once
#include <iostream>
#include <stdexcept>

class Resource {
public:
    Resource(int id) : id_(id) {}
    ~Resource() { std::cout << "���ҽ� ���� : " << id_ << std::endl; }

private:
    int id_;
};

int func3() {
    Resource r(3);
    //throw std::runtime_error("Exception from 3!\n");
    // ���ܰ� �߻����� ���� ���
    return 0;
}
int func2() {
    Resource r(2);
    func3();
    std::cout << "���� �ȵ�!" << std::endl;
    return 0;
}
int func1() {
    Resource r(1);
    func2();
    std::cout << "���� �ȵ�!" << std::endl;
    return 0;
}

void run() {
    try {
        func1();
    }
    catch (std::exception& e) {
        std::cout << "Exception : " << e.what();
    }
}