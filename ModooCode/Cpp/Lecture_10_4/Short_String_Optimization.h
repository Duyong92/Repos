#pragma once
#include <iostream>
#include <string>

// �̿� ���� new �� ���� �Լ��� �����ϸ� ��� new �����ڸ� �����ε� �ع�����.
// (� Ŭ������ ��� �Լ��� �����ϸ� �ش� Ŭ������ new �� �����ε���)
void* operator new(std::size_t count) {
	std::cout << count << " bytes �Ҵ� " << std::endl;
	return malloc(count);
}

void run() {
	std::cout << "s1 ���� --- " << std::endl;
	std::string s1 = "this is a pretty long sentence!!!";
	std::cout << "s1 ũ�� : " << sizeof(s1) << std::endl;

	std::cout << "s2 ���� --- " << std::endl;
	std::string s2 = "short sentence";
	std::cout << "s2 ũ�� : " << sizeof(s2) << std::endl;

	std::cout << std::endl << "���ڿ� �ڿ� s�� �߰��ϴ� ���" << std::endl;
	using namespace std::literals;

	auto s3 = "hello"s;
	std::cout << "s3 ���� : " << s3.size() << std::endl;
	
	std::cout << std::endl;
	std::cout << std::endl << "�� ���� literal ���� ���" << std::endl;
	std::wstring wstr = L"hello";
	std::cout << "wstr ���� : " << wstr.size() << std::endl;

	std::cout << std::endl << "Raw string literal" << std::endl;
	std::string str = R"(asdfasdf
�� �ȿ���
� �͵��� �͵�
// �̷��͵� �ǰ�
#define hasldfjalskdfj
\n\n <--- Escape ���ص� ��
	)";
	std::cout << str << std::endl;

	std::cout << std::endl << "()�� �ִ� ���" << std::endl;
	std::string str1 = R"foo(
)"; <-- ���õ�
)foo";

	std::cout << str1 << std::endl;
}