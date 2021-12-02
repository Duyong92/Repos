#pragma once

#include <iostream>
#include <string>

template <typename String>
std::string StrCat(const String& s) {
    return std::string(s);
}

template <typename String, typename... Strings>
std::string StrCat(const String& s, Strings... strs) {
    //��������� ���ǵȴ�.
    return std::string(s) + StrCat(strs...);
}

void run() {
    // std::string �� const char* �� ȥ���ؼ� ��� �����ϴ�.
    std::cout << StrCat(std::string("this"), " ", "is", " ", std::string("a"),
        " ", std::string("sentence"));
}