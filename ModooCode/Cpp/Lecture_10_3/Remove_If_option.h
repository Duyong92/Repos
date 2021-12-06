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
struct is_odd {
    int* num_delete;

    is_odd(int* num_delete) : num_delete(num_delete) {}

    bool operator()(const int& i) {
        if ((*num_delete) >= 2) return false;

        if (i % 2 == 1) {
            (*num_delete)++;
            return true;
        }

        return false;
    }
};
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

    std::cout << "���Ϳ��� Ȧ���� ���� ���� 2�� ���� ---" << std::endl;
    // C++ ǥ�ؿ� ������ remove_if �� ������ �������� ��,
    // ������ ȣ�⿡ ���� ���� ���°� �޶����� �ȵȴ�.
    int num_delete = 0;
    vec.erase(std::remove_if(vec.begin(), vec.end(), is_odd(&num_delete)), vec.end());
    print(vec.begin(), vec.end());
}