#include "Header_15_4.h"

void worker(std::promise<string>* p) {
	// ����� �����ϴ� ���. �ش� ����� future�� ����.
	p->set_value("some data");
}

void Promise_Future() {
	std::promise<string> p;

	// �̷��� string �����͸� ���� �ְڴٴ� ���.
	std::future<string> data = p.get_future();

	std::thread t(worker, &p);

	// �̷��� ��ӵ� �����͸� ���� ������ ��ٸ���.
	data.wait();

	// wait �� �����ߴٴ� ���� future �� �����Ͱ� �غ�Ǿ��ٴ� �ǹ�.
	// ����� wait ���� �׳� get �ص� wait �� �Ͱ� ����.
	std::cout << "���� ������ : " << data.get() << std::endl;

	t.join();
}