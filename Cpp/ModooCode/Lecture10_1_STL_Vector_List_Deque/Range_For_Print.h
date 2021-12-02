#pragma once
#include <iostream>
#include <vector>

template <typename T>
void print_vector(std::vector<T>& vec) {
    // ��ü ���͸� ����ϱ�
    for (typename std::vector<T>::iterator itr = vec.begin(); itr != vec.end();
        ++itr) {
        std::cout << *itr << std::endl;
    }
}

template <typename T>
void print_vector_range_based(std::vector<T>& vec) {
    // ��ü ���͸� ����ϱ�
    for (const auto& elem : vec) {
        std::cout << elem << std::endl;
    }
}

void run() {
    std::vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);
    vec.push_back(4);

    std::cout << "print_vector" << std::endl;
    print_vector(vec);
    std::cout << "print_vector_range_based" << std::endl;
    print_vector_range_based(vec);
}