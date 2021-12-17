#include "Header_15_2.h"

using std::mutex;
using std::thread;
using std::ref;

void worker1(mutex& m1, mutex& m2) {
	for (int i = 0; i < 10000; i++) {
		std::lock_guard<mutex> lock1(m1);
		std::lock_guard<mutex> lock2(m2);
		// Do something
	}
}

void worker2(mutex& m1, mutex& m2) {
	for (int i = 0; i < 10000; i++) {
		std::lock_guard<mutex> lock2(m2);
		std::lock_guard<mutex> lock1(m1);
		// Do something
	}
}

void Deadlock() {
	int counter = 0;
	mutex m1, m2;

	// thread ���� ���� lock�� �浹�� ���� ��� ����(starvation) �� �߻��Ѵ�.
	thread t1(worker1, ref(m1), ref(m2));
	thread t2(worker2, ref(m1), ref(m2));

	t1.join();
	t2.join();

	std::cout << "��!" << std::endl;
}