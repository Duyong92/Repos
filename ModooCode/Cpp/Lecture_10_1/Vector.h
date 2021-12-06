#pragma once
#include <iostream>
#include <vector>

// iterator 가 std::vector<T> 의 의존 타입이기 때문에 typename 을 추가해줘야한다.
template <typename T>
void print_vector(std::vector<T>& vec) {
	// 전체 벡터를 출력하기
	std::cout << "[";
	for (typename std::vector<T>::iterator itr = vec.begin(); itr != vec.end();
		++itr) {
		std::cout << *itr << " ";
	}
	std::cout << "]" << std::endl;
}

void run() {
	std::vector<int> vec;
	vec.push_back(10);	// 맨 뒤에 10 추가
	vec.push_back(20);	// 맨 뒤에 20 추가
	vec.push_back(30);	// 맨 뒤에 30 추가
	vec.push_back(40);	// 맨 뒤에 40 추가
	vec.push_back(20);	

	// 벡터의 크기를 리턴하는 함수인 size 의 경우, 리턴하는 값의 탑은 size_type 멤버 타입으로 정의한다.
	for (std::vector<int>::size_type i = 0; i < vec.size(); i++) {
		std::cout << "vec 의 " << i + 1 << " 번째 원소 :: " << vec[i] << std::endl;
	}

	// vector 의 경우 임의 위치 insert, erase 는 최악의 효율을 자랑한다.

	//  반복자(iterator)
	// 컨테이너에 원소에 접근할 수 있는 포인터와 같은 객체이다.
	// begin 은 첫 원소를 가르키고 end 마지막 위치를 가르킨다. ( 비어 있을 경우 NULL 을 반환한다. )

	// int arr[4] = {10, 20, 30, 40}
	 // *(arr + 2) == arr[2] == 30;
	 // *(itr + 2) == vec[2] == 30;

	//std::vector<int>::iterator itr = vec.begin() + 2;
	//std::cout << "3 번째 원소 :: " << *itr << std::endl << std::endl;

	//std::cout << "처음 벡터 상태" << std::endl;
	//print_vector(vec);
	//std::cout << "----------------------------" << std::endl;

	//// vec[2] 앞에 15 추가
	//vec.insert(vec.begin() + 2, 15);
	//print_vector(vec);

	//std::cout << "----------------------------" << std::endl;
	//// vec[3] 제거
	//vec.erase(vec.begin() + 3);
	//print_vector(vec);

	std::cout << "처음 벡터 상태" << std::endl;
	print_vector(vec);

	std::vector<int>::iterator itr = vec.begin();
	//std::vector<int>::iterator end_itr = vec.end();

	//for (; itr != vec.end()/*end_itr*/; ++itr) {
	//	if (*itr == 20) {
	//		vec.erase(itr);
	//		itr = vec.begin();
	//	}
	//}
	for (std::vector<int>::size_type i = 0; i != vec.size(); i++)
	{
		if (vec[i] == 20)
		{
			vec.erase(vec.begin() + i);
			i--;
		}
	}

	std::cout << "값이 20 인 원소를 지운다!" << std::endl;
	print_vector(vec);
}


