#include "Header_15_1.h"
//#pragma warning(disable:4996)
#include <cstdio>
#include <vector>

using std::vector;
using std::thread;

void worker(vector<int>::iterator start, vector<int>::iterator end, int* result) {
	int sum = 0;
	for (auto itr = start; itr < end; ++itr) {
		sum += *itr;
	}
	*result = sum;

	// �������� id �� ���Ѵ�.
	thread::id this_id = std::this_thread::get_id();
	/* 
	C2673 : ������ �ƴ� �׸��� _Param_(2) ���� ���޵Ǿ����ϴ�. 'printf' �� ���� ȣ�⿡�� ������ �ʿ��մϴ�.
	���� ����: 'class std::thread::id'. ������ ���� ���޵Ǵ� ��� %p ��(��) ����ؾ� �մϴ�.
	 
	printf("������ %x ���� %d ���� %d ���� ����� ��� : %d \n", this_id, *start, *(end - 1), sum);
	*/
	printf("������ %p ���� %d ���� %d ���� ����� ��� : %d \n", this_id, *start, *(end - 1), sum);
}

void worker_1(int& counter) {
	for (int i = 0; i < 10000; i++) {
		counter += 1;
	}
}

void Thread_advanced() {
	vector<int> data(10000);
	for (int i = 0; i < 10000; i++) {
		data[i] = i;
	}

	// �� �����忡�� ���� �κ� �յ��� �����ϴ� ����
	vector<int> partial_sums(4);

	vector<thread> workers;
	for (int i = 0; i < 4; i++) {
		workers.push_back(thread(	worker, 
									data.begin() + i * 2500, 
									data.begin() + (i + 1) * 2500, 
									&partial_sums[i]));
	}

	for (int i = 0; i < 4; i++) {
		workers[i].join();
	}

	int total = 0;
	for (int i = 0; i < 4; i++) {
		total += partial_sums[i];
	}
	std::cout << "��ü �� : " << total << std::endl;
};

void Thread_advanced_1() {
	int counter = 0;
	vector<thread> workers_1;
	for (int i = 0; i < 4; i++) {
		// ���۷����� �����Ϸ��� ref �Լ��� ���ξ� �Ѵ� (���� ���� bind �Լ� ����)
		workers_1.push_back(thread(worker_1, std::ref(counter)));
	}

	for (int i = 0; i < 4; i++) {
		workers_1[i].join();
	}

	std::cout << "Counter ���� �� : " << counter << std::endl;
}