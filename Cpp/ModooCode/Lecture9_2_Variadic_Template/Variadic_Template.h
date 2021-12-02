#pragma once

#include <iostream>

using std::cout; 
using std::endl;

int i = 0;

//print 함수의 순서가 바뀌는 경우 정의되지 않은 함수라며 오류가 생긴다.
template <typename T>
void print(T arg) {
	cout << "1번째 print : " << arg << endl;
}

//typename 뒤에 ...로 오는 것을 함수 파라미터 팩이라고 한다.
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

	//여기서부터는 테스트이다.
	i = 0;
	print("HELLO");
	i = 0;
	print("hello", 'a', 1.78, 2);
}