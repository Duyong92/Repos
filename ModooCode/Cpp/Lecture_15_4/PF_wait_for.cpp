#include "Header_15_4.h"

#include <chrono>
#include <exception>

void worker(std::promise<void>* p) {
	std::this_thread::sleep_for(std::chrono::seconds(10));
	p->set_value();
}

void PF_wait_for() {
	// void �� ��� ��� ��ü�� �������� ������, future �� set �� �Ǿ���
	// �ȵǾ������� ������ ��ġ �÷����� ������ ������ �� �ֽ��ϴ�.
	std::promise<void> p;

	// �̷��� string �����͸� ���� �ְڴٴ� ���
	std::future<void> data = p.get_future();

	std::thread t(worker, &p);

	// �̷��� ��ӵ� �����͸� ���� ������ ��ٸ���.
	while (true) {
		std::future_status status = data.wait_for(std::chrono::seconds(1));

		// ���� �غ� �ȵ�
		if (status == std::future_status::timeout) {
			std::cerr << ">";
		}
		// promise �� future �� ������.
		else if (status == std::future_status::ready) {
			break;
		}
	}

	t.join();
}