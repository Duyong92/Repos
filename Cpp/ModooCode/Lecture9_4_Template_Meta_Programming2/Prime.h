#pragma once
#include <iostream>

//int 타입의 N 을 static const int 의 INT 로 선언한다.
template <int N>
struct INT {
	static const int num = N;
};

//INT 의 산술연산 처리를 한다.
template <typename a, typename b>
struct add {
	typedef INT<a::num + b::num> result;
};
template <typename a, typename b>
struct divide {
	typedef INT<a::num / b::num> result;
};

//1,2,3 의 INT 를 미리 선언한다.
using one = INT<1>;
using two = INT<2>;
using three = INT<3>;

template <typename N, typename d>
struct check_div {
	// result 중에서 한 개라도 true 면 전체가 true 이다.
	static const bool result = (N::num % d::num == 0) ||
		check_div<N, typename add<d, one>::result>::result;
};

template <typename N>
struct _is_prime {
	static const bool result = !check_div<N, two>::result;
};

//INT 2,3 을 미리 소수 처리를 한다.
template <>
struct _is_prime<two> {
	static const bool result = true;
};
template <>
struct _is_prime<three> {
	static const bool result = true;
};

template <typename N>
struct check_div<N, typename divide<N, two>::result> {
	static const bool result = (N::num % (N::num / 2) == 0);
};

template <int N>
struct is_prime {
	static const bool result = _is_prime<INT<N>>::result;
};

void run()
{
	std::cout << std::boolalpha;
	std::cout << "Is 2 prime ? :: " << is_prime<2>::result << std::endl; // true
	//result = _is_prime<INT<2>>::result
	//result = _is_prime<two>::result
	//result = true
	std::cout << "Is 10 prime ? :: " << is_prime<10>::result << std::endl; // false
	//result = _is_prime<INT<10>>::result
	//result = !check_div<INT<10>,two>::result
	//result = !((10 % 2 == 0) || check_div<INT<10>, typename add<two, one>>::result)
	//result = !(TRUE || ...)
	//result = FALSE
	std::cout << "Is 11 prime ? :: " << is_prime<11>::result << std::endl; // true
	//result = _is_prime<INT<11>>::result
	//result = !check_div<INT<11>,two>::result
	//result = !((11 % 2 == 0) || check_div<INT<11>, typename add<two, one>>::result)
	//result = !((11 % 2 == 0) || check_div<INT<11>, INT<3>>::result)
	//result = !(FALSE || ((11 % 3 == 0) || check_div<INT<11>, INT<4>>::result))
	//result = !(FALSE || (FALSE ||... || check_div<INT<11>, INT<11>>::result))...)
	std::cout << "Is 61 prime ? :: " << is_prime<61>::result << std::endl; // true
	//result = _is_prime<INT<61>>::result
	//result = !check_div<INT<61>, two>::result
	//result = !((61 % 2 == 0) || check_div<INT<61>,add<two, one>::result>::result)
	//result = !((FALSE) || check_div<INT<61>,three>::result)
	//result = !((FALSE) || ((61 % 3 == 0) || check_div<INT<61>, INT<4>>::result))
	//result = !((FALSE) || ((FALSE) || .... || check_div<INT<61>, INT<61>>::result))...)
	//result = !((FALSE) || ((FALSE) || .... || ((61 % 61 == 0) || check_div<INT<61>, INT<62>>::result))...)
	//result = !(TRUE) 이상하다?
}