#include "Header_14_1.h"

int some_func1(const std::string& a) {
	std::cout << "Func1 호출! " << a << std::endl;
	return 0;
}

struct S {
	void operator()(char c) { std::cout << "Func2 호출! " << c << std::endl; }
};

//#include <typeinfo>

void std_Function() {
	std::function<int(const std::string&)> f1 = some_func1;
	std::function<void(char)> f2 = S();
	std::function<void()> f3 = []() {std::cout << "Func3 호출! " << std::endl; };
	//std::cout << "type_info().name(): " << std::type_info(f1).name() << std::endl;

	std::string s = "some_func1";

	//std::function<int(const std::string&)> f4 = s;

	f1("HELLO");
	f2('c');
	f3();
}

class A {
	int c;

public:
	A(int c) : c(c) {}
	//int some_func(){ std::cout << "내부 데이터: " << c << std::endl; }
	int some_func() {
		std::cout << "비상수 함수: " << ++c << std::endl;
		return c;
	}

	int some_const_function() const {
		std::cout << "상수 함수: " << c << std::endl;
		return c;
	}

	static void st() {}
};

void std_Function_1() {
	A a(5);
	// E0300: C++ 바인딩된 함수에 대한 포인터는 함수를 호출하는 데에만 사용할 수 있습니다.
	// E0415: "int()"에서 "std::function<int ()>"(으)로 변환하기 위한 적절한 생성자가 없습니다.
	//std::function<int()> f1 = a.some_func;
	std::function<int(A&)> f1 = &A::some_func;
	std::function<int(const A&)> f2 = &A::some_const_function;

	f1(a);
	f2(a);
}