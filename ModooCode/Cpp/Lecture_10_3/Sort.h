#pragma once
#include <algorithm>
#include <iostream>
#include <vector>

template <typename Iter>
void print(Iter begin, Iter end) {
    while (begin != end) {
        std::cout << *begin << " ";
        begin++;
    }
    std::cout << std::endl;
}
void run() {
    std::vector<int> vec;
    vec.push_back(5);
    vec.push_back(3);
    vec.push_back(1);
    vec.push_back(6);
    vec.push_back(4);
    vec.push_back(7);
    vec.push_back(2);

    std::cout << "���� �� ----" << std::endl;
    print(vec.begin(), vec.end());

    // sort �� ��� �������� �ݺ���(RandomAccesIterator) Ÿ���� �����ؾ��Ѵ�.
    // vector, deque �� �����ϴ�.
    // �⺻������ ������������ ������ �ȴ�.
    std::sort(vec.begin(), vec.end());

    std::cout << "���� �� ----" << std::endl;
    print(vec.begin(), vec.end());
}