#pragma once
#include <iostream>
#include <stdexcept>

class Resource {
public:
    Resource(int id) : id_(id) {}
    ~Resource() { std::cout << "리소스 해제 : " << id_ << std::endl; }

private:
    int id_;
};

int func3() {
    Resource r(3);
    //throw std::runtime_error("Exception from 3!\n");
    // 예외가 발생하지 않을 경우
    return 0;
}
int func2() {
    Resource r(2);
    func3();
    std::cout << "실행 안됨!" << std::endl;
    return 0;
}
int func1() {
    Resource r(1);
    func2();
    std::cout << "실행 안됨!" << std::endl;
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