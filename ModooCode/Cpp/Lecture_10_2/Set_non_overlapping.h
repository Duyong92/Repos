#pragma once
#include <iostream>
#include <set>

template <typename T>
void print_set(std::set<T>& s) {
    // ���� ��� ���ҵ��� ����ϱ�
    std::cout << "[ ";
    // list �� ���������� ���� for�� ����� �� �ִ�.
    for (const auto& elem : s) {
        std::cout << elem << " ";
    }
    std::cout << " ] " << std::endl;
}

void run() {
    std::set<int> s;
    s.insert(10);
    s.insert(20);
    s.insert(30);
    s.insert(20);
    s.insert(10);

    print_set(s);
}