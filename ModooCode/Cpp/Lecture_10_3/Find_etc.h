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

void run() {
    std::vector<int> vec;
    vec.push_back(5);
    vec.push_back(3);
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);
    vec.push_back(4);

    std::cout << "vec 기본 형태" << std::endl;
    print(vec.begin(), vec.end());

    // find 함수는 중복되는 값이 있어도 먼저 찾은 값을 리턴하게 된다.
    std::cout << "3 의 index 값은?" << std::endl;
    auto result = std::find(vec.begin(), vec.end(), 3);
    std::cout << "3 은 " << std::distance(vec.begin(), result) + 1 << " 번째 원소"
        << std::endl;

    // find 를 지원하는 컨테이너의 경우 find 를 사용하는게 이상적이다.
    // distance 를 통해 index 값을 추출할 수 있다.
    std::cout << "3 의 모든 index 값은?" << std::endl;
    auto current = vec.begin();
    while (true) {
        current = std::find(current, vec.end(), 3);
        if (current == vec.end()) break;
        std::cout << "3 은 " << std::distance(vec.begin(), current) + 1
            << " 번째 원소" << std::endl;
        current++;
    }
    std::cout << "3 로 나눈 나머지가 2 인 원소?" << std::endl;
    current = vec.begin();
    while (true) {
        current =
            std::find_if(current, vec.end(), [](int i) { return i % 3 == 2; });
        if (current == vec.end()) break;
        std::cout << "3 으로 나눈 나머지가 2 인 원소는 : " << *current << " 이다 "
            << std::endl;
        current++;
    }
}