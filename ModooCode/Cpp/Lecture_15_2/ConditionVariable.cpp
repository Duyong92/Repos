#include "Header_15_2.h"

#include <chrono>
#include <condition_variable>
#include <queue>
#include <string>

using std::chrono::milliseconds;
using std::queue;
using std::mutex;
using std::string;
using std::thread;
using std::vector;

void producer_cv(queue<string>* downloaded_pages, mutex* m, int index, std::condition_variable* cv) {
	for (int i = 0; i < 5; i++) {
		// 웹사이트를 다운로드 하는데 걸리는 시간이라 생각하면 된다.
		// 각 쓰레드 별로 다운로드 하는데 걸리는 시간이 다르다.
		std::this_thread::sleep_for(milliseconds(100 * index));
		string content = "웹사이트 : " + std::to_string(i) + " from thread(" + std::to_string(index) + ")\n";

		// data 는 쓰레드 사이에서 공유되므로 critical section 에 넣어야 한다.
		m->lock();
		downloaded_pages->push(content);
		m->unlock();

		// consumer 에게 content 가 준비되었으을 알린다.
		cv->notify_one();
	}
}

void consumer_cv(queue<string>* downloaded_pages, mutex* m, int* num_processed, std::condition_variable* cv) {
	while (*num_processed < 25) {
		std::unique_lock<mutex> unique_lock(*m);

		cv->wait(unique_lock, [&] {return !downloaded_pages->empty()
			|| *num_processed == 25; });

		if (*num_processed == 25) {
			unique_lock.unlock();
			return;
		}

		// 맨 앞의 페이지를 읽고 대기 목록에서 제거한다.
		string content = downloaded_pages->front();
		downloaded_pages->pop();

		(*num_processed)++;
		unique_lock.unlock();

		// content 를 처리한다.
		std::cout << content;
		std::this_thread::sleep_for(std::chrono::milliseconds(80));
	}
}

void ConditionVariable() {
	queue<string> downloaded_pages;
	mutex m;
	std::condition_variable cv;

	vector<thread> producers;
	for (int i = 0; i < 5; i++) {
		producers.push_back(thread(producer_cv, &downloaded_pages, &m, i + 1, &cv));
	}

	int num_processed = 0;
	vector<thread> consumers;
	for (int i = 0; i < 3; i++) {
		consumers.push_back(thread(consumer_cv, &downloaded_pages, &m, &num_processed, &cv));
	}

	for (int i = 0; i < 5; i++)
		producers[i].join();

	// 나머지 자고 있는 쓰레드들을 모두 깨운다.
	cv.notify_all();

	for (int i = 0; i < 3; i++)
		consumers[i].join();
}