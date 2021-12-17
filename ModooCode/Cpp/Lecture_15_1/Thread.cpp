#include "Header_15_1.h"

void func1() {
	for (int i = 0; i < 10; i++) {
		std::cout << "쓰레드 1 작동 중! \n";
	}
}

void func2() {
	for (int i = 0; i < 10; i++) {
		std::cout << "쓰레드 2 작동 중! \n";
	}
}

void func3() {
	for (int i = 0; i < 10; i++) {
		std::cout << "쓰레드 3 작동 중! \n";
	}
}

void Thread() {
	std::thread t1(func1);
	std::thread t2(func2);
	std::thread t3(func3);

	/*
	t1.join();
	t2.join();
	t3.join();
	*/

	t1.detach();
	t2.detach();
	t3.detach();

	std::cout << "메인 함수 종료 \n";
}