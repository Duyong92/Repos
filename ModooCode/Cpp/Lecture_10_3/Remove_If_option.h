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

    std::cout << "처음 vec 상태 ------" << std::endl;
    print(vec.begin(), vec.end());

    std::cout << "벡터에서 홀수인 원소 앞의 2개 제거 ---" << std::endl;
    // C++ 표준에 따르면 remove_if 를 실제로 구현했을 때,
    // 히전의 호출에 의해 내부 상태가 달라지면 안된다.
    int num_delete = 0;
    vec.erase(std::remove_if(vec.begin(), vec.end(), is_odd(&num_delete)), vec.end());
    print(vec.begin(), vec.end());
}