#pragma once
#include <iostream>
#include <vector>

int run() {
    std::vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);

    // ������ ���� ����ϱ�
   /* for (std::vector<int>::size_type i = vec.size() - 1; i >= 0; i--) {
        std::cout << vec[i] << std::endl;
    }*/
    // range-based for ��
    // elem �� vec �� ���ҵ��� �� ���� ���� ����Ǽ� ���� �˴ϴ�.
    for (int elem : vec) {
        std::cout << "���� : " << elem << std::endl;
    }

    return 0;
}