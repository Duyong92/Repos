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
struct User {
    std::string name;
    int age;

    User(std::string name, int age) : name(name), age(age) {}

    bool operator<(const User& u) const { return age < u.age; }
};

std::ostream& operator<<(std::ostream& o, const User& u) {
    o << u.name << " , " << u.age;
    return o;
}

void run() {
    std::vector<User> vec;
    for (int i = 0; i < 100; i++) {
        std::string name = "";
        name.push_back('a' + i / 26);
        name.push_back('a' + i % 26);
        vec.push_back(User(name, static_cast<int>(rand() % 10)));
    }

    std::vector<User> vec2 = vec;

    std::cout << "���� �� ----" << std::endl;
    print(vec.begin(), vec.end());

    //std::cout << "���� �� ----" << std::endl;
    //std::sort(vec.begin(), vec.end());
    //print(vec.begin(), vec.end());

    // stable_sort �� ��� ó���� �־��� ���� �״�� �����Ѵ�.
    // stable_sort �� ��� �־��� ��� 0(n(log n)^2)���� �۵��ϰ� �ȴ�.
    std::cout << "stable_sort �� ��� ---" << std::endl;
    std::stable_sort(vec2.begin(), vec2.end());
    print(vec2.begin(), vec2.end());
}