#include "Header_14_1.h"

/*
placeholders의 객체의 개수는 libstdc++ 의 경우 _1 부터 _29 까지 정의되어 있다.
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

    // 두 번째 인자는 무시된다.
    add_with_2(3, 4);

    auto subtract_from_2 = std::bind(subtract, std::placeholders::_1, 2);
    auto negate =
        std::bind(subtract, std::placeholders::_2, std::placeholders::_1);

    subtract_from_2(3);  // 3 - 2 를 계산한다.
    negate(4, 2);        // 2 - 4 를 계산한다
}

struct S {
    int data;
    S(int data) : data(data) { std::cout << "일반 생성자 호출!" << std::endl; }
    S(const S& s) {
        std::cout << "복사 생성자 호출!" << std::endl;
        data = s.data;
    }

    S(S&& s) {
        std::cout << "이동 생성자 호출!" << std::endl;
        data = s.data;
    }
};

void do_something(S& s1, const S& s2) { s1.data = s2.data + 3; }

void std_Bind_1() {
    S s1(1), s2(2);

    std::cout << "Before: " << s1.data << std::endl;

    // s1 이 그대로 전달된 것이 아니라 s1 의 복사본이 전달됨!
    auto do_something_with_s1 = std::bind(do_something, /*s1*/
                                                        std::ref(s1), std::placeholders::_1);
    do_something_with_s1(s2);

    std::cout << "After: " << s1.data << std::endl;
}