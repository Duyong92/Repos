#include "Header_14_1.h"

int some_func1(const std::string& a) {
	std::cout << "Func1 ȣ��! " << a << std::endl;
	return 0;
}

struct S {
	void operator()(char c) { std::cout << "Func2 ȣ��! " << c << std::endl; }
};

//#include <typeinfo>

void std_Function() {
	std::function<int(const std::string&)> f1 = some_func1;
	std::function<void(char)> f2 = S();
	std::function<void()> f3 = []() {std::cout << "Func3 ȣ��! " << std::endl; };
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
	//int some_func(){ std::cout << "���� ������: " << c << std::endl; }
	int some_func() {
		std::cout << "���� �Լ�: " << ++c << std::endl;
		return c;
	}

	int some_const_function() const {
		std::cout << "��� �Լ�: " << c << std::endl;
		return c;
	}

	static void st() {}
};

void std_Function_1() {
	A a(5);
	// E0300: C++ ���ε��� �Լ��� ���� �����ʹ� �Լ��� ȣ���ϴ� ������ ����� �� �ֽ��ϴ�.
	// E0415: "int()"���� "std::function<int ()>"(��)�� ��ȯ�ϱ� ���� ������ �����ڰ� �����ϴ�.
	//std::function<int()> f1 = a.some_func;
	std::function<int(A&)> f1 = &A::some_func;
	std::function<int(const A&)> f2 = &A::some_const_function;

	f1(a);
	f2(a);
}