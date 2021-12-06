#pragma once
#include <algorithm>
#include <functional>
#include <iostream>
#include <string>
#include <vector>

template <typename Iter>
void print(Iter begin, Iter end) {
    while (begin != end) {
        std::cout << "[" << *begin << "] ";
        begin++;
    }
    std::cout << std::endl;
}
void run() {
    std::vector<int> vec;
    vec.push_back(5);
    vec.push_back(3);
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);
    vec.push_back(4);

    std::cout << "ó�� vec ���� ------" << std::endl;
    print(vec.begin(), vec.end());

    std::cout << "���Ϳ��� ���� 3 �� ���� ���� ---" << std::endl;
    // remove �Լ��� ��� �ݺ����� Ÿ���� ForwardIterator �̴�.
    vec.erase(std::remove(vec.begin(), vec.end(), 3), vec.end());
    print(vec.begin(), vec.end());
}