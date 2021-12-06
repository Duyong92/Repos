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

    std::cout << "vec �⺻ ����" << std::endl;
    print(vec.begin(), vec.end());

    // find �Լ��� �ߺ��Ǵ� ���� �־ ���� ã�� ���� �����ϰ� �ȴ�.
    std::cout << "3 �� index ����?" << std::endl;
    auto result = std::find(vec.begin(), vec.end(), 3);
    std::cout << "3 �� " << std::distance(vec.begin(), result) + 1 << " ��° ����"
        << std::endl;

    // find �� �����ϴ� �����̳��� ��� find �� ����ϴ°� �̻����̴�.
    // distance �� ���� index ���� ������ �� �ִ�.
    std::cout << "3 �� ��� index ����?" << std::endl;
    auto current = vec.begin();
    while (true) {
        current = std::find(current, vec.end(), 3);
        if (current == vec.end()) break;
        std::cout << "3 �� " << std::distance(vec.begin(), current) + 1
            << " ��° ����" << std::endl;
        current++;
    }
    std::cout << "3 �� ���� �������� 2 �� ����?" << std::endl;
    current = vec.begin();
    while (true) {
        current =
            std::find_if(current, vec.end(), [](int i) { return i % 3 == 2; });
        if (current == vec.end()) break;
        std::cout << "3 ���� ���� �������� 2 �� ���Ҵ� : " << *current << " �̴� "
            << std::endl;
        current++;
    }
}