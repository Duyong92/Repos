#pragma once
#include <iostream>
#include <string>

void* operator new(std::size_t count) {
    std::cout << count << " bytes �Ҵ� " << std::endl;
    return malloc(count);
}

// ���ڿ��� "very" ��� �ܾ ������ true �� ������
//bool contains_very(const std::string& str) {
//    return str.find("very") != std::string::npos;
//}
bool contains_very(std::string_view str)
{
    return str.find("very") != std::string_view::npos;
}

void run() {
    // �Ϲ������� std::string ��ü�� ���ʿ��ϰ� �����ȴ�.
    std::cout << std::boolalpha << contains_very("c++ string is very easy to use")
        << std::endl;

    std::cout << contains_very("c++ string is not easy to use") << std::endl;

    std::string str = "some long long long long long long string";
    std::cout << "--------------------" << std::endl;
    std::cout << contains_very(str) << std::endl;
}