#include "Header_14_1.h"

/*
mem_fn �� �׸� ���� �������� �ʴµ�, ���� �Լ��ε� ������ �۾��� ������ �� �ֱ� �����̴�.
*/

void Mem_fn() {
	std::vector<int > a(1);
	std::vector<int > b(2);
	std::vector<int > c(3);
	std::vector<int > d(4);

	std::vector<std::vector<int>> container;
	container.push_back(a);
	container.push_back(b);
	container.push_back(c);
	container.push_back(d);
	
	// �Ź� function �� ������ֱ� �����ϴ�.
	//std::function<size_t(const std::vector<int>&)> sz_func = &std::vector<int>::size;

	std::vector<int> size_vec(4);
	// C2064: ���� �μ��� �޾Ƶ��̴� �Լ��� ������ �ʽ��ϴ�.
	std::transform(container.begin(), container.end(), size_vec.begin(), /*&std::vector<int>::size*/
																		 /*sz_func*/
																		 std::mem_fn(&std::vector<int>::size));
	for (auto itr = size_vec.begin(); itr != size_vec.end(); ++itr) {
		std::cout << "���� ũ�� :: " << *itr << std::endl;
	}
}
