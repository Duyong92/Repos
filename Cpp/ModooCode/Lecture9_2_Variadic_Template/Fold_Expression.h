#pragma once

#include <iostream>

//C++17 이상 사용 가능하다.
template <typename... Ints>
int sum_all(Ints... nums) {
	return (... + nums);
}

void run() {
	// 1 + 4 + 2 + 3 + 10
	std::cout << sum_all(1, 4, 2, 3, 10) << std::endl;
}