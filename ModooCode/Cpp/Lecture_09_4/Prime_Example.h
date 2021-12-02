#pragma once
#include <iostream>

template <int N>
struct INT {
    static const int num = N;
};

template <typename a, typename b>
struct add {
    typedef INT<a::num + b::num> result;
};

template <typename a, typename b>
struct divide {acknowledge
    typedef INT<a::num / b::num> result;
};

using one = INT<1>;
using two = INT<2>;
using three = INT<3>;

template <typename N, typename d>
struct check_div {
    // result 중에서 한 개라도 true 면 전체가 true
    static const bool result = (N::num % d::num == 0) ||
        check_div<N, typename add<d, one>::result>::result;
};

template <typename N>
struct _is_prime {
    static const bool result = !check_div<N, two>::result;
};

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

int run() {
    std::cout << std::boolalpha;
    std::cout << "Is 2 prime ? :: " << is_prime<2>::result << std::endl;
    std::cout << "Is 10 prime ? :: " << is_prime<10>::result << std::endl;
    std::cout << "Is 11 prime ? :: " << is_prime<11>::result << std::endl;
    std::cout << "Is 61 prime ? :: " << is_prime<61>::result << std::endl;
    /*
     is_prime<61>::result
    => _is_prime<INT<61>>::result
    => !check_div<INT<61>, two>::result
    => !((INT<61>::num % two::num == 0) || check_div<INT<61>, typename add<two, one>::result>::result)
    => !((61 % 2 == 0) || check_div<INT<61>, INT<3>>::result)
    => !(FALSE || 
        ((INT<61>::num % INT<3>::num == 0) || check_div<INT<61>, typename add<INT<3>, one>::result>::result))
    => !(FALSE || 
        (FALSE || check_div<INT<61>, INT<4>>::result))
    => !(FALSE || (FALSE || 
        ((INT<61>::num % INT<4>::num == 0) || check_div<INT<61>, typename add<INT<4>, one>::result>::result)))
        .
        .
        .
        .
    // check_div<N, typename divide<N, two>::result> 템플릿에 걸려서 재귀함수가 멈춘다.
    // check_div<INT<61>, typename divide<INT<61>, two>::result
    // check_div<INT<61>, INT<30>>
    => !(FALSE || (FALSE ||  ... (FALSE || check_div<INT<61>, INT<30>>::result))
    => !(FALSE || (FALSE ||  ... (FALSE || (INT<61>::num % (INT<61>::num / 2) == 0)...)
    => !(FALSE || (FALSE ||  ... (FALSE || (1) == 0)))...)
    => !(FALSE || (FALSE ||  ... (FALSE || FALSE)))...)
    => !(FALSE) == TRUE!!!!
    */
    return 0;
}