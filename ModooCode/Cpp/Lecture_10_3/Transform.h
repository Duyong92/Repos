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

    std::vector<int> vec2(6, 0);

    std::cout << "ó�� vec �� vec2 ���� ------" << std::endl;
    print(vec.begin(), vec.end());
    print(vec2.begin(), vec2.end());

    std::cout << "���� ��ü�� 1 �� ���Ѵ�" << std::endl;
    // transform (���� �ݺ���, �� �ݺ���, ����� ������ �����̳��� ���� �ݺ���, Pred)
    // �����ϴ� �����̳��� ũ�Ⱑ ������ �����̳ʺ��� �ּ��� ���ų� Ŀ�� �Ѵ�.
    std::transform(vec.begin(), vec.end(), vec.begin(),
        [](int i) { return i + 1; });
    print(vec.begin(), vec.end());

    std::cout << "vec ��ü�� 1 �� ���� ���� vec2 �� ���� -- " << std::endl;
    std::transform(vec.begin(), vec.end(), vec2.begin(),
        [](int i) { return i + 1; });
    print(vec.begin(), vec.end());
    print(vec2.begin(), vec2.end());
}