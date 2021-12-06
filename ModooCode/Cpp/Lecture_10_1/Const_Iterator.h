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
void run() {
    std::vector<int> vec;
    vec.push_back(10);
    vec.push_back(20);
    vec.push_back(30);
    vec.push_back(40);

    std::cout << "초기 vec 상태" << std::endl;
    print_vector(vec);

    // itr 은 vec[2] 를 가리킨다.
    std::vector<int>::iterator itr = vec.begin() + 2;

    // vec[2] 의 값을 50으로 바꾼다.
    *itr = 50;

    std::cout << "---------------" << std::endl;
    print_vector(vec);

    std::vector<int>::const_iterator citr = vec.cbegin() + 2;

    // 상수 반복자가 가리키는 값은 바꿀수 없다. 불가능!
    // 상수 반족자는 참고만 하고 싶을 경우 사용한다.
    *citr = 30;
}