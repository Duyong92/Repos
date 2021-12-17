#include "Header_15_2.h"

#include <chrono>  // std::chrono::miliseconds
#include <queue>
#include <string>

using std::string;
using std::mutex;
using std::thread;
using std::vector;

void producer(std::queue<string>* downloaded_pages, mutex* m, int index) {
	for (int i = 0; i < 5; i++) {
		// ������Ʈ�� �ٿ�ε� �ϴµ� �ɸ��� �ð��̶� �����ϸ� �ȴ�.
		// �� ������ ���� �ٿ�ε� �ϴµ� �ɸ��� �ð��� �ٸ���.
		std::this_thread::sleep_for(std::chrono::milliseconds(100*index));
		string content = "������Ʈ : " + std::to_string(i) + " from thread(" + std::to_string(index) + ")\n";

		// data �� ������ ���̿��� �����ǹǷ� critical section �� �־�� �Ѵ�.
		m->lock();
		downloaded_pages->push(content);
		m->unlock();
	}
}

void consumer(std::queue<string>* downloaded_pages, mutex* m, int* num_processed) {
	// ��ü ó���ϴ� ������ ������ 5 * 5 = 25 ��.
	while (*num_processed < 25) {
		// C26111: ȣ���ڰ� 'std::Mutex_base::lock' �Լ��� ȣ���ϱ� ���� '*m' ��� �������� ���Ѵ�.
		m->lock();
		// ���� ���� �ٿ�ε��� �������� ���ٸ� �ٽ� ���.
		if (downloaded_pages->empty()) {
			m->unlock();	// (Quiz) ���⼭ unlock �� ���Ѵٸ� ��� �ɱ�?

			// 10 �и��� �ڿ� �ٽ� Ȯ���Ѵ�.
			std::this_thread::sleep_for(std::chrono::milliseconds(10));
			continue;
		}

		// �� ���� �������� �а� ��� ��Ͽ��� �����Ѵ�.
		string content = downloaded_pages->front();
		downloaded_pages->pop();

		(*num_processed)++;
		m->unlock();

		// content �� ó���Ѵ�.
		std::cout << content;
		std::this_thread::sleep_for(std::chrono::milliseconds(80));
	}
}

void Producer_Consumer() {
	// ���� �ٿ�ε��� �������� ����Ʈ��, ���� ó������ ���� �͵��̴�.
	std::queue<string> downloaded_pages;
	mutex m;

	vector<thread> producers;
	for (int i = 0; i < 5; i++)
		producers.push_back(thread(producer, &downloaded_pages, &m, i + 1));

	int num_processed = 0;
	vector<thread> consumers;
	for (int i = 0; i < 3; i++) {
		consumers.push_back(thread(consumer, &downloaded_pages, &m, &num_processed));
	}

	for (int i = 0; i < 5; i++)
		producers[i].join();
	for (int i = 0; i < 3; i++)
		consumers[i].join();
}