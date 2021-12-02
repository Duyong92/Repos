#pragma once

#include <cstring>
#include <iostream>
#include <string>

int i = 0;

size_t GetStringSize(const char* s) { return strlen(s); }

size_t GetStringSize(const std::string& s) { return s.size(); }

template <typename String, typename... Strings>
size_t GetStringSize(const String& s, Strings... strs) {
    return GetStringSize(s) + GetStringSize(strs...);
}

void AppendToString(std::string* concat_str) { return; }

template <typename String, typename... Strings>
void AppendToString(std::string* concat_str, const String& s, Strings... strs) {
    std::cout << "before : " << *concat_str << std::endl;
    concat_str->append(s);
    //" " 빈칸이 있었기 때문에 반복하는 모습을 보였던 것이다.
    std::cout << i++ << " after : " << *concat_str << std::endl;
    AppendToString(concat_str, strs...);
}

template <typename String, typename... Strings>
std::string StrCat(const String& s, Strings... strs) {
    // 먼저 합쳐질 문자열의 총 길이를 구한다.
    size_t total_size = GetStringSize(s, strs...);

    // reserve 를 통해 미리 공간을 할당해 놓는다.
    std::string concat_str;
    concat_str.reserve(total_size);

    concat_str = s;
    AppendToString(&concat_str, strs...);

    return concat_str;
}

void run() {
    // std::string 과 const char* 을 혼합해서 사용 가능하다.
    std::cout << StrCat(std::string("this"), " ", "is", " ", std::string("a"),
        " ", std::string("sentence"));
}