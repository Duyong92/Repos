#include "Header_15_4.h"

#include <exception>
#include <future>

void worker_exp(std::promise<string>* p) {
	try {
		throw std::runtime_error("Some Error!");
	}
	catch (...) {
		// set_exception 에는 exception_ptr 를 전달해야 한다.
		p->set_exception(std::current_exception());
	}
}

void worker_test() {
	std::cout << "\n";
}

void PF_exp() {
	std::promise<string> p;

	// 미래에 string 데이터를 돌려 주겠다는 약속.
	std::future<string> data = p.get_future();

	std::thread t(worker_exp, &p);
	std::thread t_test(worker_test);
	std::thread t_test_2(worker_test);

	// 미래에 약속된 데이터를 받을 때까지 기다린다.
	data.wait();

	try {
		data.get();
	}
	catch (const std::exception& e) {
		std::cout << "예외 : " << e.what() << std::endl;
	}

	t.join();
	t_test.join();
	t_test_2.join();
}