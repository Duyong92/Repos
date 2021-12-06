#pragma once
#include <iostream>
#include <set>
#include <string>

template <typename T>
void print_set(std::set<T>& s) {
    // ���� ��� ���ҵ��� ����ϱ�
    for (const auto& elem : s) {
        std::cout << elem << " " << std::endl;
    }
}
class Todo {
    int priority;  // �߿䵵. ���� ���� ���Ѱ�!
    std::string job_desc;

public:
    Todo(int priority, std::string job_desc)
        : priority(priority), job_desc(job_desc) {}

    bool operator < (const Todo& t) const {
        if (priority == t.priority) {
            std::cout << "if (" << priority << " == " << t.priority << ")" << std::endl;
            std::cout << "(" << job_desc << " < " << t.job_desc << ")" << std::endl;
            std::cout << ((job_desc < t.job_desc) ? "��" : "����") << std::endl;
            return job_desc < t.job_desc;
        }
        std::cout << "if (" << priority << " != " << t.priority << ")" << std::endl;
        std::cout << "(" << priority << " > " << t.priority << ")" << std::endl;
        std::cout << ((priority > t.priority) ? "��" : "����") << std::endl;
        return priority > t.priority;
    }

    friend std::ostream& operator<<(std::ostream& o, const Todo& td);
};

std::ostream& operator<<(std::ostream& o, const Todo& td) {
    o << "[ �߿䵵: " << td.priority << "] " << td.job_desc;
    return o;
}

void run() {
    std::set<Todo> todos;

    std::cout << "1, ���ϱ� ����" << std::endl;
    todos.insert(Todo(1, "�� �ϱ�"));
    std::cout << "2, ���� ���� �ϱ� ����" << std::endl;
    todos.insert(Todo(2, "���� ���� �ϱ�"));
    std::cout << "1, ���α׷��� ������Ʈ ����" << std::endl;
    todos.insert(Todo(1, "���α׷��� ������Ʈ"));
    std::cout << "3, ģ�� ������ ����" << std::endl;
    todos.insert(Todo(3, "ģ�� ������"));
    std::cout << "2, ��ȭ ���� ����" << std::endl;
    todos.insert(Todo(2, "��ȭ ����"));

    print_set(todos);

    std::cout << "--------------" << std::endl;
    std::cout << "������ ���´ٸ�!" << std::endl;
    todos.erase(todos.find(Todo(2, "���� ���� �ϱ�")));
    print_set(todos);
}