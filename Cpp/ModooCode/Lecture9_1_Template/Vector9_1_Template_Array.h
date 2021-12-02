#pragma once

#include <iostream>
#include <array>


/*
str::array<int,5> �� �ϳ��� Ÿ���� �Ǿ���ȴ�.
void print_array(const std::array<int, 5>& arr) {
	for (int i = 0; i < arr.size(); i++) {
		std::cout << arr[i] << " ";
	}
	std::cout << std::endl;
}


void run() {
	//���ø� ���ڷ� �迭 ũ�⸦ ����� ��� array�� �����̴�.
	// ��ġ C ������ �迭 ó�� {} �� ���� �迭�� ������ �� �ִ�.
	// {} ������ 16 - 1 ������ �ڼ��� �ٷ�Ƿ� ���⼭�� �׳� �̷���
	// ���� �Ǵ±��� �ϰ� �����ϰ� �Ѿ�� �˴ϴ�.
	std::array<int, 5> arr = { 1, 2, 3, 4, 5 };
	// int arr[5] = {1, 2, 3, 4, 5}; �� ����

	for (int i = 0; i < arr.size(); i++) {
		std::cout << arr[i] << " ";
	}
	std::cout << std::endl;

	std::array<int, 5> arr2 = { 1, 2, 3, 4, 5 };
	print_array(arr2);
}
*/

//���ø�ȭ ��Ű�� �Ʒ��� ���� ���ϰ� �ȴ�.
template <typename T>
//���ø��� ���� array�� Ÿ���� ���� ���������� �ʾ� �ڵ尡 ������ ���δ�.
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