#include "Header_14_1.h"

struct S {
	void operator()(int a, int b) { std::cout << "a + b = " << a + b << std::endl; }
};

void Callable() {
	S some_obj;

	// some_obj.operator()(3, 5) 와 동일한 코드이다.
	some_obj(3, 5);
}

//#include <typeinfo>

void Callable_1() {
	//auto f = [](int a, int b) { std::cout << "a + b = " << a + b << std::endl; };
	auto f = [](int a, int b) { std::cout << "a + b = " << a + b << std::endl; };
	f(3, 5);
	//std::cout << std::type_info(f).name() << std::endl;
}