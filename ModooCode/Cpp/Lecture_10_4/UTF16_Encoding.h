#pragma once
#include <iostream>
#include <string>

void run() {
    std::u16string u16_str = u"�ȳ��ϼ��� ��ο� �ڵ忡 ���� ���� ȯ���մϴ�";
    std::string jaum[] = { "��", "��", "��", "��", "��", "��", "��",
                          "��", "��", "��", "��", "��", "��", "��",
                          "��", "��", "��", "��", "��" };

    for (char16_t c : u16_str) {
        // �����ڵ� �󿡼� �ѱ��� ����
        // 0xD7A3(55203)
        if (!(0xAC00 <= c && c <= 0xD7A3)) {
            continue;
        }
        // �ѱ��� AC00(44032) ���� �����ؼ� �� �ʼ��� �� 0x24C(588) �� �� �ִ�.
        int offset = c - 0xAC00;
        int jaum_offset = offset / 0x24C;
        std::cout << jaum[jaum_offset];
    }
}