#include "Header_14_1.h"

/*
placeholders�� ��ü�� ������ libstdc++ �� ��� _1 ���� _29 ���� ���ǵǾ� �ִ�.
*/

void add(int x, int y) {
    std::cout << x << " + " << y << " = " << x + y << std::endl;
}

void subtract(int x, int y) {
    std::cout << x << " - " << y << " = " << x - y << std::endl;
}
void std_Bind() {
    auto add_with_2 = std::bind(add, 2, std::placeholders::_1);
    add_with_2(3);

    // �� ��° ���ڴ� ���õȴ�.
    add_with_2(3, 4);

    auto subtract_from_2 = std::bind(subtract, std::placeholders::_1, 2);
    auto negate =
        std::bind(subtract, std::placeholders::_2, std::placeholders::_1);

    subtract_from_2(3);  // 3 - 2 �� ����Ѵ�.
    negate(4, 2);        // 2 - 4 �� ����Ѵ�
}

struct S {
    int data;
    S(int data) : data(data) { std::cout << "�Ϲ� ������ ȣ��!" << std::endl; }
    S(const S& s) {
        std::cout << "���� ������ ȣ��!" << std::endl;
        data = s.data;
    }

    S(S&& s) {
        std::cout << "�̵� ������ ȣ��!" << std::endl;
        data = s.data;
    }
};

void do_something(S& s1, const S& s2) { s1.data = s2.data + 3; }

void std_Bind_1() {
    S s1(1), s2(2);

    std::cout << "Before: " << s1.data << std::endl;

    // s1 �� �״�� ���޵� ���� �ƴ϶� s1 �� ���纻�� ���޵�!
    auto do_something_with_s1 = std::bind(do_something, /*s1*/
                                                        std::ref(s1), std::placeholders::_1);
    do_something_with_s1(s2);

    std::cout << "After: " << s1.data << std::endl;
}