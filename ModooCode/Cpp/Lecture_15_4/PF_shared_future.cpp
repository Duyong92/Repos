#include "Header_15_4.h"

#include <chrono>
#include <thread>

void runner(std::shared_future<void>* start) {
	start->get();
	printf("1���� ���!\n");
}
void runner1(std::shared_future<void>* start) {
	start->get();
	printf("2���� ���!\n");
}
void runner2(std::shared_future<void>* start) {
	start->get();
	printf("3���� ���!\n");
}
void runner3(std::shared_future<void>* start) {
	start->get();
	printf("4���� ���!\n");
}

void timer(std::promise<void>* s) {
	std::this_thread::sleep_for(std::chrono::seconds(3));
	s->set_value();
}

void PF_shared_future() {
	std::promise<void> p;
	std::promise<void> s;
	std::shared_future<void> start = p.get_future();
	std::future<void> data = s.get_future();

	std::thread t(timer, &s);
	std::thread t1(runner, &start);
	std::thread t2(runner1, &start);
	std::thread t3(runner2, &start);
	std::thread t4(runner3, &start);

	// ����� cerr �� std::cout ���� �ٸ��� ���۸� ������� �ʱ� ������ �͹̳ο� �ٷ� ��µȴ�.
	std::cerr << "�غ�";
	while (true) {
		std::future_status status = data.wait_for(std::chrono::seconds(1));

		// ���� �غ� �ȵ�
		if (status == std::future_status::timeout) {
			std::cerr << ".";
		}
		// promise �� future �� ������.
		else if (status == std::future_status::ready) {
			std::cout << std::endl;
			break;
		}
	}
	std::cerr << "��!" << std::endl;

	p.set_value();

	t.join();
	t1.join();
	t2.join();
	t3.join();
	t4.join();
}