#pragma once

#include <iostream>

using std::cout; 
using std::endl;

int i = 0;

//print �Լ��� ������ �ٲ�� ��� ���ǵ��� ���� �Լ���� ������ �����.
template <typename T>
void print(T arg) {
	cout << "1��° print : " << arg << endl;
}

//typename �ڿ� ...�� ���� ���� �Լ� �Ķ���� ���̶�� �Ѵ�.
template<typename T, typename... Types>
void print(T arg, Types... args) {
	//int i = 0;
	cout << i++ << arg << ", ";
	print(args...);
}

void run() {
	i = 0;
	print(1, 3.1, "abc");	// 1, 3.1, abc
	i = 0;
	print(1, 2, 3, 4, 5, 6, 7);	// 1, 2, 3, 4, 5, 6, 7

	//���⼭���ʹ� �׽�Ʈ�̴�.
	i = 0;
	print("HELLO");
	i = 0;
	print("hello", 'a', 1.78, 2);
}