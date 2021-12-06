#pragma once
#include <iostream>
#include <string>

void run() {
    std::u16string u16_str = u"안녕하세용 모두에 코드에 오신 것을 환영합니다";
    std::string jaum[] = { "ㄱ", "ㄲ", "ㄴ", "ㄷ", "ㄸ", "ㄹ", "ㅁ",
                          "ㅂ", "ㅃ", "ㅅ", "ㅆ", "ㅇ", "ㅈ", "ㅉ",
                          "ㅊ", "ㅋ", "ㅌ", "ㅍ", "ㅎ" };

    for (char16_t c : u16_str) {
        // 유니코드 상에서 한글의 범위
        // 0xD7A3(55203)
        if (!(0xAC00 <= c && c <= 0xD7A3)) {
            continue;
        }
        // 한글은 AC00(44032) 부터 시작해서 한 초성당 총 0x24C(588) 개 씩 있다.
        int offset = c - 0xAC00;
        int jaum_offset = offset / 0x24C;
        std::cout << jaum[jaum_offset];
    }
}