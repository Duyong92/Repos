#include "Header_15_2.h"

/*
void worker(int& result, std::mutex& m) {
	for (int i = 0; i < 10000; i++) {
		m.lock();
		result += 1;
		// unlock �� �������� �ʴ� ��� �����(deadlock) �� �߻��ȴ�.
		m.unlock();
	}
}
*/
void worker(int& result, std::mutex& m) {
	for (int i = 0; i < 10000; i++) {
		// lock ���� �ÿ� m.lock() �� �����Ѵٰ� ���� �ȴ�.
		std::lock_guard<std::mutex> lock(m);
		result += 1;

		// scope �� ���� ������ lock �� �Ҹ�Ǹ鼭
		// m �� �˾Ƽ� unlock �Ѵ�.
	}
}

void Mutex() {
	int counter = 0;
	std::mutex m;	// �츮�� mutex ��ü

	std::vector<std::thread> workers;
	for (int i = 0; i < 4; i++) {
		workers.push_back(std::thread(worker, std::ref(counter), std::ref(m)));
	}
	for (int i = 0; i < 4; i++) {
		workers[i].join();
	}

	std::cout << "Counter ���� �� : " << counter << std::endl;
}