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

    std::cout << "정렬 전 ----" << std::endl;
    print(vec.begin(), vec.end());

    // sort 의 경우 임의접근 반복자(RandomAccesIterator) 타입을 만족해야한다.
    // vector, deque 만 가능하다.
    // 기본적으로 오름차순으로 정렬이 된다.
    std::sort(vec.begin(), vec.end());

    std::cout << "정렬 후 ----" << std::endl;
    print(vec.begin(), vec.end());
}