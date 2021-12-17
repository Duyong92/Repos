#include "Header_15_2.h"

using std::mutex;
using std::thread;
using std::ref;

void worker3(mutex& m1, mutex& m2) {
	for (int i = 0; i < 10; i++) {
		m1.lock();
		m2.lock();
		printf("Worker3 Hi! %d \n", i);

		m2.unlock();
		m1.unlock();
	}
}

void worker4(mutex& m1, mutex& m2) {
	for (int i = 0; i < 10; i++) {
		while (true) {
			m2.lock();

			// m1 �� �̹� lock �Ǿ� �ִٸ� "�� �� ��" �� �����ϰ� �ȴ�.
			if (!m1.try_lock()) {
				m2.unlock();
				continue;
			}

			printf("Worker4 Hi! %d \n", i);
			m1.unlock();
			m2.unlock();
			break;
		}
	}
}

void Deadlock_solve() {
	mutex m1, m2;  // �츮�� mutex ��ü

	thread t1(worker3, ref(m1), ref(m2));
	thread t2(worker4, ref(m1), ref(m2));

	t1.join();
	t2.join();

	std::cout << "��!" << std::endl;
}