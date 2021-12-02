#pragma once
#include <iostream>
#include <vector>

void run() {
    std::vector<int> vec;
    vec.push_back(10);  // 맨 뒤에 10 추가
    vec.push_back(20);  // 맨 뒤에 20 추가
    vec.push_back(30);  // 맨 뒤에 30 추가
    vec.push_back(40);  // 맨 뒤에 40 추가

    for (std::vector<int>::size_type i = 0; i < vec.size(); i++) {
        std::cout << "vec 의 " << i + 1 << " 번째 원소 :: " << vec[i] << std::endl;
    }
}