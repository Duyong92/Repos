#include "Header_15_4.h"

#include <exception>
#include <future>

void worker_exp(std::promise<string>* p) {
	try {
		throw std::runtime_error("Some Error!");
	}
	catch (...) {
		// set_exception ���� exception_ptr �� �����ؾ� �Ѵ�.
		p->set_exception(std::current_exception());
	}
}

void worker_test() {
	std::cout << "\n";
}

void PF_exp() {
	std::promise<string> p;

	// �̷��� string �����͸� ���� �ְڴٴ� ���.
	std::future<string> data = p.get_future();

	std::thread t(worker_exp, &p);
	std::thread t_test(worker_test);
	std::thread t_test_2(worker_test);

	// �̷��� ��ӵ� �����͸� ���� ������ ��ٸ���.
	data.wait();

	try {
		data.get();
	}
	catch (const std::exception& e) {
		std::cout << "���� : " << e.what() << std::endl;
	}

	t.join();
	t_test.join();
	t_test_2.join();
}