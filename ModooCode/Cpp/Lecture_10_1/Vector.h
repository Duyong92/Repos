#pragma once
#include <iostream>
#include <vector>

// iterator �� std::vector<T> �� ���� Ÿ���̱� ������ typename �� �߰�������Ѵ�.
template <typename T>
void print_vector(std::vector<T>& vec) {
	// ��ü ���͸� ����ϱ�
	std::cout << "[";
	for (typename std::vector<T>::iterator itr = vec.begin(); itr != vec.end();
		++itr) {
		std::cout << *itr << " ";
	}
	std::cout << "]" << std::endl;
}

void run() {
	std::vector<int> vec;
	vec.push_back(10);	// �� �ڿ� 10 �߰�
	vec.push_back(20);	// �� �ڿ� 20 �߰�
	vec.push_back(30);	// �� �ڿ� 30 �߰�
	vec.push_back(40);	// �� �ڿ� 40 �߰�
	vec.push_back(20);	

	// ������ ũ�⸦ �����ϴ� �Լ��� size �� ���, �����ϴ� ���� ž�� size_type ��� Ÿ������ �����Ѵ�.
	for (std::vector<int>::size_type i = 0; i < vec.size(); i++) {
		std::cout << "vec �� " << i + 1 << " ��° ���� :: " << vec[i] << std::endl;
	}

	// vector �� ��� ���� ��ġ insert, erase �� �־��� ȿ���� �ڶ��Ѵ�.

	//  �ݺ���(iterator)
	// �����̳ʿ� ���ҿ� ������ �� �ִ� �����Ϳ� ���� ��ü�̴�.
	// begin �� ù ���Ҹ� ����Ű�� end ������ ��ġ�� ����Ų��. ( ��� ���� ��� NULL �� ��ȯ�Ѵ�. )

	// int arr[4] = {10, 20, 30, 40}
	 // *(arr + 2) == arr[2] == 30;
	 // *(itr + 2) == vec[2] == 30;

	//std::vector<int>::iterator itr = vec.begin() + 2;
	//std::cout << "3 ��° ���� :: " << *itr << std::endl << std::endl;

	//std::cout << "ó�� ���� ����" << std::endl;
	//print_vector(vec);
	//std::cout << "----------------------------" << std::endl;

	//// vec[2] �տ� 15 �߰�
	//vec.insert(vec.begin() + 2, 15);
	//print_vector(vec);

	//std::cout << "----------------------------" << std::endl;
	//// vec[3] ����
	//vec.erase(vec.begin() + 3);
	//print_vector(vec);

	std::cout << "ó�� ���� ����" << std::endl;
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

	std::cout << "���� 20 �� ���Ҹ� �����!" << std::endl;
	print_vector(vec);
}


