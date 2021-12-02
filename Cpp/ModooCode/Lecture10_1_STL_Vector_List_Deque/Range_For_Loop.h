#pragma once
#include <iostream>
#include <vector>

void run() {
    std::vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);

    // range-based for ¹®
    for (int elem : vec) {
        std::cout << "¿ø¼Ò : " << elem << std::endl;
    }
}