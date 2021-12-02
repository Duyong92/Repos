#pragma once
#include <iostream>
#include <typeinfo>

template <int N, int D = 1>
struct Ratio {
	typedef Ratio<N, D> type;
	static const int num = N;  // 분자
	static const int den = D;  // 분모
};

template <class R1, class R2>
struct _Ratio_add {
	//Ratio 타입의 type 변수로 선언된다.
	typedef Ratio<R1::num * R2::den + R2::num * R1::den, R1::den * R2::den> type;
};

template <class R1, class R2>
//Ratio::type을 따로 호출하기 번거롭기 때문에 묶어버린다.
struct Ratio_add : _Ratio_add<R1, R2>::type {};

void run() {
	/*
	typedef Ratio<2, 3> rat;
	typedef Ratio<3, 2> rat2;
	typedef Ratio_add<rat, rat2> rat3;
	*/

	//C++11 부터 typedf 대신에 좀 더 직관적인 using 이라는 키워드를 사용할 수 있다.
	using rat = Ratio<2, 3>;
	using rat2 = Ratio<3, 2>;

	using rat3 = Ratio_add<rat, rat2>;

	std::cout << rat3::num << " / " << rat3::den << std::endl;
}