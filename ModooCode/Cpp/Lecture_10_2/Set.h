#pragma once
#include <iostream>
#include <set>

// 마찬가지로 bidirectional iterator를 사용하게 된다.
template <typename T>
void print_set(std::set<T>& s) {
    // 셋의 모든 원소들을 출력하기
    std::cout << "[ ";
    for (typename std::set<T>::iterator itr = s.begin(); itr != s.end(); ++itr) {
        std::cout << *itr << " ";
    }
    std::cout << " ] " << std::endl;
}
void run() {
    std::set<int> s;
    s.insert(10);
    s.insert(50);
    s.insert(20);
    s.insert(40);
    s.insert(30);

    std::cout << "순서대로 정렬되서 나온다" << std::endl;
    print_set(s);

    std::cout << "20 이 s 의 원소인가요? :: ";
    // s.find() 로는 std::set<>::iterator 타입을 리턴하게 된다.
    // 존재하지 않는다면 s.end() 를 리턴하게 된다.
    auto itr = s.find(20);
    if (itr != s.end()) {
        std::cout << "Yes" << std::endl;
    }
    else {
        std::cout << "No" << std::endl;
    }

    std::cout << "25 가 s 의 원소인가요? :: ";
    itr = s.find(25);
    if (itr != s.end()) {
        std::cout << "Yes" << std::endl;
    }
    else {
        std::cout << "No" << std::endl;
    }
}