#include "Header_14_1.h"

/*
mem_fn 은 그리 자주 쓰이지는 않는데, 람다 함수로도 동일한 작업을 수행할 수 있기 때문이다.
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
	
	// 매번 function 을 만들어주기 복잡하다.
	//std::function<size_t(const std::vector<int>&)> sz_func = &std::vector<int>::size;

	std::vector<int> size_vec(4);
	// C2064: 항은 인수를 받아들이는 함수로 계산되지 않습니다.
	std::transform(container.begin(), container.end(), size_vec.begin(), /*&std::vector<int>::size*/
																		 /*sz_func*/
																		 std::mem_fn(&std::vector<int>::size));
	for (auto itr = size_vec.begin(); itr != size_vec.end(); ++itr) {
		std::cout << "벡터 크기 :: " << *itr << std::endl;
	}
}
