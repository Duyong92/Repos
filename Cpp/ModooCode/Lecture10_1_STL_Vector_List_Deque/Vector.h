#pragma once
#include <iostream>
#include <vector>

void run() {
    std::vector<int> vec;
    vec.push_back(10);  // �� �ڿ� 10 �߰�
    vec.push_back(20);  // �� �ڿ� 20 �߰�
    vec.push_back(30);  // �� �ڿ� 30 �߰�
    vec.push_back(40);  // �� �ڿ� 40 �߰�

    for (std::vector<int>::size_type i = 0; i < vec.size(); i++) {
        std::cout << "vec �� " << i + 1 << " ��° ���� :: " << vec[i] << std::endl;
    }
}