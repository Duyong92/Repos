#pragma once
// List 는 컨테이너 자체에서는 시작 원소와 마지막 원소의 위치만을 기억한다.
// 때문에, [] , at 함수가 정의 되어 있지 않는다.
// 하나씩 찾아가는 작업은 느리지만 찾아서 처리하는 능력은 vector 보다 우수하다.

#include <iostream>
#include <list>

void run() {
    std::list<int> lst;

    lst.push_back(10);
    lst.push_back(20);
    lst.push_back(30);
    lst.push_back(40);


    // itr++ , itr-- 와 같은 연산 밖에 수행이 안된다.
    // itr + 5  <- 불가능!
    for (std::list<int>::iterator itr = lst.begin(); itr != lst.end(); ++itr) {
        std::cout << *itr << std::endl;
    }
}