#pragma once
#include <iostream>
#include <vector>

template <typename T>
void print_vector(std::vector<T>& vec) {
    // 전체 벡터를 출력하기
    for (typename std::vector<T>::iterator itr = vec.begin(); itr != vec.end();
        ++itr) {
        std::cout << *itr << std::endl;
    }
}

template <typename T>
void print_vector_range_based(std::vector<T>& vec) {
    // 전체 벡터를 출력하기
    // 향상된 for 문을 사용하였다.
    // elem 에 const auto& 를 선언하여 vec 의 원소들을 상수 레퍼런스로 접근하게 되었다.
    for (const auto& elem : vec) {
        std::cout << elem << std::endl;
    }
}

int run() {
    std::vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);
    vec.push_back(4);

    std::cout << "print_vector" << std::endl;
    print_vector(vec);
    std::cout << "print_vector_range_based" << std::endl;
    print_vector_range_based(vec);

    return 0;
}