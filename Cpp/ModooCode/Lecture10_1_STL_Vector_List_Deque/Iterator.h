#pragma once
// �ݺ��� ��� ����
#include <iostream>
#include <vector>

/*
template <typename T>
void print_vector(std::vector<T>& vec) {
    // ��ü ���͸� ����ϱ�
    for (typename std::vector<T>::iterator itr = vec.begin(); itr != vec.end();
        ++itr) {
        std::cout << *itr << std::endl;
    }
}
*/

template <typename T>
void print_vector(std::vector<T>& vec) {
    // ��ü ���͸� ����ϱ�
    std::cout << "[ ";
    for (typename std::vector<T>::iterator itr = vec.begin(); itr != vec.end();
        ++itr) {
        std::cout << *itr << " ";
    }
    std::cout << "]";
}

void run() {
    std::vector<int> vec;
    vec.push_back(10);
    vec.push_back(20);
    vec.push_back(30);
    vec.push_back(40);
    
    /*
    // ��ü ���͸� ����ϱ�
    for (std::vector<int>::iterator itr = vec.begin(); itr != vec.end(); ++itr) {
        std::cout << *itr << std::endl;
    }

    // int arr[4] = {10, 20, 30, 40}
    // *(arr + 2) == arr[2] == 30;
    // *(itr + 2) == vec[2] == 30;

    std::vector<int>::iterator itr = vec.begin() + 2;
    std::cout << "3 ��° ���� :: " << *itr << std::endl << std::endl;

    std::cout << "ó�� ���� ����" << std::endl;
    print_vector(vec);
    std::cout << "----------------------------" << std::endl;

    // vec[2] �տ� 15 �߰�
    vec.insert(vec.begin() + 2, 15);
    print_vector(vec);

    std::cout << "----------------------------" << std::endl;
    // vec[3] ����
    vec.erase(vec.begin() + 3);
    print_vector(vec);
    std::cout << std::endl;
    */

    std::cout << "ó�� ���� ����" << std::endl;
    print_vector(vec);

    std::vector<int>::iterator itr = vec.begin();
    std::vector<int>::iterator end_itr = vec.end();

    for (; itr != vec.end(); ++itr) {
        if (*itr == 20) {
            vec.erase(itr);
            itr = vec.begin();
        }
    }

    std::cout << std::endl << "���� 20 �� ���Ҹ� �����!" << std::endl;
    print_vector(vec);

}