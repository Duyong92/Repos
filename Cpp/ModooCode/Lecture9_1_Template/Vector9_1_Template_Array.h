#pragma once

#include <iostream>
#include <array>


/*
str::array<int,5> 가 하나의 타입이 되어버렸다.
void print_array(const std::array<int, 5>& arr) {
	for (int i = 0; i < arr.size(); i++) {
		std::cout << arr[i] << " ";
	}
	std::cout << std::endl;
}


void run() {
	//템플릿 인자로 배열 크기를 명시할 경우 array의 사용법이다.
	// 마치 C 에서의 배열 처럼 {} 을 통해 배열을 정의할 수 있다.
	// {} 문법은 16 - 1 강에서 자세히 다루므로 여기서는 그냥 이렇게
	// 쓰면 되는구나 하고 이해하고 넘어가면 됩니다.
	std::array<int, 5> arr = { 1, 2, 3, 4, 5 };
	// int arr[5] = {1, 2, 3, 4, 5}; 와 동일

	for (int i = 0; i < arr.size(); i++) {
		std::cout << arr[i] << " ";
	}
	std::cout << std::endl;

	std::array<int, 5> arr2 = { 1, 2, 3, 4, 5 };
	print_array(arr2);
}
*/

//템플릿화 시키면 아래와 같이 변하게 된다.
template <typename T>
//템플릿을 통해 array의 타입을 따로 지정해주지 않아 코드가 간편해 보인다.
void print_array(const T& arr) {
	for (int i = 0; i < arr.size(); i++) {
		std::cout << arr[i] << " ";
	}
	std::cout << std::endl;
}

void run() {
	std::array<int, 5> arr = { 1, 2, 3, 4, 5 };
	std::array<int, 7> arr2 = { 1, 2, 3, 4, 5, 6, 7 };
	std::array<int, 3> arr3 = { 1, 2, 3 };

	print_array(arr);
	print_array(arr2);
	print_array(arr3);
}