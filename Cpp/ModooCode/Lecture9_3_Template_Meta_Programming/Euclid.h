#pragma once
#include <iostream>

template <int X, int Y>
struct GCD {
	static const int value = GCD<Y, X% Y>::value;
};

template <int X>
struct GCD<X, 0> {
	static const int value = X;
};

//일반적인 식을 계산할 때는 아래와 같이 계산한다.
int gcd(int a, int b) {
	if (b == 0) {
		return a;
	}

	return gcd(b, a % b);
}

void run() {
	std::cout << "gcd (36, 24) :: " << GCD<36, 24>::value << std::endl;
}