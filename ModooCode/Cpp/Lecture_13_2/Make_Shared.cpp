#pragma once
#include "Header_13_2.h"
#ifdef MAKE_SHARED
#include <iostream>
#include <memory>

class A : public std::enable_shared_from_this<A> {
    int* data;

public:
    A() {
        data = new int[100];
        std::cout << "ÀÚ¿øÀ» È¹µæÇÔ!" << std::endl;
    }

    ~A() {
        std::cout << "¼Ò¸êÀÚ È£Ãâ!" << std::endl;
        delete[] data;
    }

    //std::shared_ptr<A> get_shared_ptr() { return std::shared_ptr<A>(this); }
    std::shared_ptr<A> get_shared_ptr() { return shared_from_this(); }
};

void Make_Shared() {
    /*
    std::shared_ptr<A> pa1(a);
    std::shared_ptr<A> pa2(a);
    */

    // A* a = new A();
    std::shared_ptr<A> pa1 = std::make_shared<A>();
    std::shared_ptr<A> pa2 = pa1->get_shared_ptr();

    std::cout << pa1.use_count() << std::endl;
    std::cout << pa2.use_count() << std::endl;
}
#endif // MAKE_SHARED
#ifndef MAKE_SHARED
void Make_Shared() {}
#endif // !MAKE_SHARED
