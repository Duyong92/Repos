#include "Header_15_4.h"

#include <chrono>
#include <exception>

void worker(std::promise<void>* p) {
	std::this_thread::sleep_for(std::chrono::seconds(10));
	p->set_value();
}

void PF_wait_for() {
	// void 의 경우 어떠한 객체도 전달하지 않지만, future 가 set 이 되었냐
	// 안되었느냐의 유무로 마치 플래그의 역할을 수행할 수 있습니다.
	std::promise<void> p;

	// 미래에 string 데이터를 돌려 주겠다는 약속
	std::future<void> data = p.get_future();

	std::thread t(worker, &p);

	// 미래에 약속된 데이터를 받을 때까지 기다린다.
	while (true) {
		std::future_status status = data.wait_for(std::chrono::seconds(1));

		// 아직 준비가 안됨
		if (status == std::future_status::timeout) {
			std::cerr << ">";
		}
		// promise 가 future 를 설정함.
		else if (status == std::future_status::ready) {
			break;
		}
	}

	t.join();
}