#pragma once
// List �� �����̳� ��ü������ ���� ���ҿ� ������ ������ ��ġ���� ����Ѵ�.
// ������, [] , at �Լ��� ���� �Ǿ� ���� �ʴ´�.
// �ϳ��� ã�ư��� �۾��� �������� ã�Ƽ� ó���ϴ� �ɷ��� vector ���� ����ϴ�.

#include <iostream>
#include <list>

void run() {
    std::list<int> lst;

    lst.push_back(10);
    lst.push_back(20);
    lst.push_back(30);
    lst.push_back(40);


    // itr++ , itr-- �� ���� ���� �ۿ� ������ �ȵȴ�.
    // itr + 5  <- �Ұ���!
    for (std::list<int>::iterator itr = lst.begin(); itr != lst.end(); ++itr) {
        std::cout << *itr << std::endl;
    }
}