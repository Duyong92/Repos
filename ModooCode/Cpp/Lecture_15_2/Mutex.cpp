#include "Header_15_2.h"

/*
void worker(int& result, std::mutex& m) {
	for (int i = 0; i < 10000; i++) {
		m.lock();
		result += 1;
		// unlock 을 실행하지 않는 경우 데드락(deadlock) 이 발생된다.
		m.unlock();
	}
}
*/
void worker(int& result, std::mutex& m) {
	for (int i = 0; i < 10000; i++) {
		// lock 생성 시에 m.lock() 을 실행한다고 보면 된다.
		std::lock_guard<std::mutex> lock(m);
		result += 1;

		// scope 를 빠져 나가면 lock 이 소멸되면서
		// m 을 알아서 unlock 한다.
	}
}

void Mutex() {
	int counter = 0;
	std::mutex m;	// 우리의 mutex 객체

	std::vector<std::thread> workers;
	for (int i = 0; i < 4; i++) {
		workers.push_back(std::thread(worker, std::ref(counter), std::ref(m)));
	}
	for (int i = 0; i < 4; i++) {
		workers[i].join();
	}

	std::cout << "Counter 최종 값 : " << counter << std::endl;
}