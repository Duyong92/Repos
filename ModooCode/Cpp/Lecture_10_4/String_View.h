#pragma once
#include <iostream>
#include <string>

void* operator new(std::size_t count) {
    std::cout << count << " bytes 할당 " << std::endl;
    return malloc(count);
}

// 문자열에 "very" 라는 단어가 있으면 true 를 리턴함
//bool contains_very(const std::string& str) {
//    return str.find("very") != std::string::npos;
//}
bool contains_very(std::string_view str)
{
    return str.find("very") != std::string_view::npos;
}

void run() {
    // 암묵적으로 std::string 객체가 불필요하게 생성된다.
    std::cout << std::boolalpha << contains_very("c++ string is very easy to use")
        << std::endl;

    std::cout << contains_very("c++ string is not easy to use") << std::endl;

    std::string str = "some long long long long long long string";
    std::cout << "--------------------" << std::endl;
    std::cout << contains_very(str) << std::endl;
}