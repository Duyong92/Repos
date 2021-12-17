#include "Header_15_2.h"

using std::vector;
using std::thread;

void worker(int& counter) {
	for (int i = 0; i < 10000; i++) {
		counter += 1;
	}
}

void RaceCondition() {
	int counter = 0;

	vector<thread> workers;
	for (int i = 0; i < 4; i++) {
		// ���۷����� �����Ϸ��� ref �Լ��� ���ξ� �Ѵ� (���� ���� bind �Լ� ����)
		workers.push_back(thread(worker, std::ref(counter)));
	}

	for (int i = 0; i < 4; i++) {
		workers[i].join();
	}

	std::cout << "Counter ���� �� : " << counter << std::endl;
}