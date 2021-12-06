#pragma once
#include <iostream>
#include <string>
//#ifdef _WIN32
//    #include <Windows.h>
//#endif

void run() 
{
//#ifdef _WIN32
//    SetConsoleOutputCP(CP_UTF8);
//#endif

    //                   1 234567890 1 2 34 5 6
    std::string str = u8"이건 UTF-8 문자열 입니다";
    size_t i = 0;
    size_t len = 0;

    std::cout << str << std::endl;

    while (i < str.size()) {
        int char_size = 0;

        if ((str[i] & 0b11111000) == 0b11110000) {
            char_size = 4;
            std::cout << "0b11111000로 분류" << std::endl;
        }
        else if ((str[i] & 0b11110000) == 0b11100000) {
            char_size = 3;
            std::cout << "0b11110000로 분류" << std::endl;
        }
        else if ((str[i] & 0b11100000) == 0b11000000) {
            char_size = 2;
            std::cout << "0b11100000로 분류" << std::endl;
        }
        else if ((str[i] & 0b10000000) == 0b00000000) {
            char_size = 1;
            std::cout << "0b10000000로 분류" << std::endl;
        }
        else {
            std::cout << "이상한 문자 발견!" << std::endl;
            char_size = 1;
        }

        std::cout << str.substr(i, char_size) << std::endl;

        i += char_size;
        len++;
    }
    std::cout << "문자열의 실제 길이 : " << len << std::endl;
}