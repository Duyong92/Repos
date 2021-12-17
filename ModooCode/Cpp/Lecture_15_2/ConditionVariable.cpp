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
		// ������Ʈ�� �ٿ�ε� �ϴµ� �ɸ��� �ð��̶� �����ϸ� �ȴ�.
		// �� ������ ���� �ٿ�ε� �ϴµ� �ɸ��� �ð��� �ٸ���.
		std::this_thread::sleep_for(milliseconds(100 * index));
		string content = "������Ʈ : " + std::to_string(i) + " from thread(" + std::to_string(index) + ")\n";

		// data �� ������ ���̿��� �����ǹǷ� critical section �� �־�� �Ѵ�.
		m->lock();
		downloaded_pages->push(content);
		m->unlock();

		// consumer ���� content �� �غ�Ǿ����� �˸���.
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

		// �� ���� �������� �а� ��� ��Ͽ��� �����Ѵ�.
		string content = downloaded_pages->front();
		downloaded_pages->pop();

		(*num_processed)++;
		unique_lock.unlock();

		// content �� ó���Ѵ�.
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

	// ������ �ڰ� �ִ� ��������� ��� �����.
	cv.notify_all();

	for (int i = 0; i < 3; i++)
		consumers[i].join();
}