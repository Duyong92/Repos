#pragma once
#include <iostream>
#include <typeinfo>

template <int N, int D = 1>
struct Ratio {
	typedef Ratio<N, D> type;
	static const int num = N;  // ����
	static const int den = D;  // �и�
};

template <class R1, class R2>
struct _Ratio_add {
	//Ratio Ÿ���� type ������ ����ȴ�.
	typedef Ratio<R1::num * R2::den + R2::num * R1::den, R1::den * R2::den> type;
};

template <class R1, class R2>
//Ratio::type�� ���� ȣ���ϱ� ���ŷӱ� ������ ���������.
struct Ratio_add : _Ratio_add<R1, R2>::type {};

void run() {
	/*
	typedef Ratio<2, 3> rat;
	typedef Ratio<3, 2> rat2;
	typedef Ratio_add<rat, rat2> rat3;
	*/

	//C++11 ���� typedf ��ſ� �� �� �������� using �̶�� Ű���带 ����� �� �ִ�.
	using rat = Ratio<2, 3>;
	using rat2 = Ratio<3, 2>;

	using rat3 = Ratio_add<rat, rat2>;

	std::cout << rat3::num << " / " << rat3::den << std::endl;
}