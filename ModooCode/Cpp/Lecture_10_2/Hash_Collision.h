#pragma once
#include <iostream>
#include <string>
#include <unordered_set>

template <typename K>
void print_unordered_set(const std::unordered_set<K>& m) {
    // ���� ��� ���ҵ��� ����ϱ�
    for (const auto& elem : m) {
        std::cout << elem << std::endl;
    }
}

template <typename K>
void is_exist(std::unordered_set<K>& s, K key) {
    auto itr = s.find(key);
    if (itr != s.end()) {
        std::cout << key << " �� ����!" << std::endl;
    }
    else {
        std::cout << key << " �� ����" << std::endl;
    }
}
void run() {
    std::unordered_set<std::string> s;

    s.insert("hi");
    s.insert("my");
    s.insert("name");
    s.insert("is");
    s.insert("psi");
    s.insert("welcome");
    s.insert("to");
    s.insert("c++");

    print_unordered_set(s);
    std::cout << "----------------" << std::endl;
    is_exist(s, std::string("c++"));
    is_exist(s, std::string("c"));

    std::cout << "----------------" << std::endl;
    std::cout << "'hi' �� ����" << std::endl;
    s.erase(s.find("hi"));
    is_exist(s, std::string("hi"));
}