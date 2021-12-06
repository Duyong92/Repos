#pragma once
#include <iostream>
#include <set>

// ���������� bidirectional iterator�� ����ϰ� �ȴ�.
template <typename T>
void print_set(std::set<T>& s) {
    // ���� ��� ���ҵ��� ����ϱ�
    std::cout << "[ ";
    for (typename std::set<T>::iterator itr = s.begin(); itr != s.end(); ++itr) {
        std::cout << *itr << " ";
    }
    std::cout << " ] " << std::endl;
}
void run() {
    std::set<int> s;
    s.insert(10);
    s.insert(50);
    s.insert(20);
    s.insert(40);
    s.insert(30);

    std::cout << "������� ���ĵǼ� ���´�" << std::endl;
    print_set(s);

    std::cout << "20 �� s �� �����ΰ���? :: ";
    // s.find() �δ� std::set<>::iterator Ÿ���� �����ϰ� �ȴ�.
    // �������� �ʴ´ٸ� s.end() �� �����ϰ� �ȴ�.
    auto itr = s.find(20);
    if (itr != s.end()) {
        std::cout << "Yes" << std::endl;
    }
    else {
        std::cout << "No" << std::endl;
    }

    std::cout << "25 �� s �� �����ΰ���? :: ";
    itr = s.find(25);
    if (itr != s.end()) {
        std::cout << "Yes" << std::endl;
    }
    else {
        std::cout << "No" << std::endl;
    }
}