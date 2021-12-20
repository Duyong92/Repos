#include "Header_15_4.h"

#include <chrono>
#include <thread>

void runner(std::shared_future<void>* start) {
	start->get();
	printf("1번마 출발!\n");
}
void runner1(std::shared_future<void>* start) {
	start->get();
	printf("2번마 출발!\n");
}
void runner2(std::shared_future<void>* start) {
	start->get();
	printf("3번마 출발!\n");
}
void runner3(std::shared_future<void>* start) {
	start->get();
	printf("4번마 출발!\n");
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

	// 참고로 cerr 는 std::cout 과는 다르게 버퍼를 사용하지 않기 때문에 터미널에 바로 출력된다.
	std::cerr << "준비";
	while (true) {
		std::future_status status = data.wait_for(std::chrono::seconds(1));

		// 아직 준비가 안됨
		if (status == std::future_status::timeout) {
			std::cerr << ".";
		}
		// promise 가 future 를 설정함.
		else if (status == std::future_status::ready) {
			std::cout << std::endl;
			break;
		}
	}
	std::cerr << "땅!" << std::endl;

	p.set_value();

	t.join();
	t1.join();
	t2.join();
	t3.join();
	t4.join();
}