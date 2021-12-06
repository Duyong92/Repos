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

    std::cout << "처음 vec 상태 ------" << std::endl;
    print(vec.begin(), vec.end());

    std::cout << "벡터에서 홀수인 원소 제거 ---" << std::endl;
    vec.erase(std::remove_if(vec.begin(), vec.end(),
        [](int i) -> bool { return i % 2 == 1; }),
        // return 타입을 생략하면 return 문을 보고 알아서 컴파일한다.
        // [](int i) -> { return i % 2 == 1; }),
        vec.end());
    print(vec.begin(), vec.end());
}

// lambda 함수를 사용하고 싶다면,
// auto func = [](int i) { return i % 2 == 1; };
// func(4);  // false;
// 와 같이 표기할 수 있다.