#pragma once
#include <iostream>
#include <vector>

int run() {
    std::vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);

    // 끝에서 부터 출력하기
   /* for (std::vector<int>::size_type i = vec.size() - 1; i >= 0; i--) {
        std::cout << vec[i] << std::endl;
    }*/
    // range-based for 문
    // elem 에 vec 의 원소들이 매 루프 마다 복사되서 들어가게 됩니다.
    for (int elem : vec) {
        std::cout << "원소 : " << elem << std::endl;
    }

    return 0;
}