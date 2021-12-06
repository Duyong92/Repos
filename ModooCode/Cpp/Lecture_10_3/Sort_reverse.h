#pragma once
#include <algorithm>
#include <iostream>
#include <vector>
#include <functional>
//#include <xstddef>

template <typename Iter>
void print(Iter begin, Iter end) {
    while (begin != end) {
        std::cout << *begin << " ";
        begin++;
    }
    std::cout << std::endl;
}
//struct int_compare {
//    bool operator()(const int& a, const int& b) const { return a > b; }
//};
//template <typename T>
//struct greater_comp {
//    bool operator()(const T& a, const T& b) const { return a > b; }
//};
void run() {
    std::vector<int> vec;
    vec.push_back(5);
    vec.push_back(3);
    vec.push_back(1);
    vec.push_back(6);
    vec.push_back(4);
    vec.push_back(7);
    vec.push_back(2);

    std::cout << "정렬 전 ----" << std::endl;
    print(vec.begin(), vec.end());
    //std::sort(vec.begin(), vec.end(), int_compare());
    //std::sort(vec.begin(), vec.end(), greater_comp<int>());
    std::sort(vec.begin(), vec.end(), std::greater<int>());

    std::cout << "정렬 후 ----" << std::endl;
    print(vec.begin(), vec.end());
}