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

	// 쓰레드의 id 를 구한다.
	thread::id this_id = std::this_thread::get_id();
	/* 
	C2673 : 정수가 아닌 항목이 _Param_(2) 으로 전달되었습니다. 'printf' 에 대한 호출에는 정수가 필요합니다.
	실제 형식: 'class std::thread::id'. 포인터 값이 전달되는 경우 %p 을(를) 사용해야 합니다.
	 
	printf("쓰레드 %x 에서 %d 부터 %d 까지 계산한 결과 : %d \n", this_id, *start, *(end - 1), sum);
	*/
	printf("쓰레드 %p 에서 %d 부터 %d 까지 계산한 결과 : %d \n", this_id, *start, *(end - 1), sum);
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

	// 각 쓰레드에서 계산된 부분 합들을 저장하는 벡터
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
	std::cout << "전체 합 : " << total << std::endl;
};

void Thread_advanced_1() {
	int counter = 0;
	vector<thread> workers_1;
	for (int i = 0; i < 4; i++) {
		// 레퍼런스로 전달하려면 ref 함수로 감싸야 한다 (지난 강좌 bind 함수 참조)
		workers_1.push_back(thread(worker_1, std::ref(counter)));
	}

	for (int i = 0; i < 4; i++) {
		workers_1[i].join();
	}

	std::cout << "Counter 최종 값 : " << counter << std::endl;
}