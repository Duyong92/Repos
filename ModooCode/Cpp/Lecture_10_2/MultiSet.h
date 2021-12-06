#pragma once
#include <iostream>
#include <set>
#include <string>

template <typename T>
void print_set(std::set<T>& s) {
    // 셋의 모든 원소들을 출력하기
    for (const auto& elem : s) {
        std::cout << elem << " " << std::endl;
    }
}
class Todo {
    int priority;  // 중요도. 높을 수록 급한것!
    std::string job_desc;

public:
    Todo(int priority, std::string job_desc)
        : priority(priority), job_desc(job_desc) {}

    bool operator < (const Todo& t) const {
        if (priority == t.priority) {
            std::cout << "if (" << priority << " == " << t.priority << ")" << std::endl;
            std::cout << "(" << job_desc << " < " << t.job_desc << ")" << std::endl;
            std::cout << ((job_desc < t.job_desc) ? "참" : "거짓") << std::endl;
            return job_desc < t.job_desc;
        }
        std::cout << "if (" << priority << " != " << t.priority << ")" << std::endl;
        std::cout << "(" << priority << " > " << t.priority << ")" << std::endl;
        std::cout << ((priority > t.priority) ? "참" : "거짓") << std::endl;
        return priority > t.priority;
    }

    friend std::ostream& operator<<(std::ostream& o, const Todo& td);
};

std::ostream& operator<<(std::ostream& o, const Todo& td) {
    o << "[ 중요도: " << td.priority << "] " << td.job_desc;
    return o;
}

void run() {
    std::set<Todo> todos;

    std::cout << "1, 농구하기 삽입" << std::endl;
    todos.insert(Todo(1, "농구 하기"));
    std::cout << "2, 수학 숙제 하기 삽입" << std::endl;
    todos.insert(Todo(2, "수학 숙제 하기"));
    std::cout << "1, 프로그래밍 프로젝트 삽입" << std::endl;
    todos.insert(Todo(1, "프로그래밍 프로젝트"));
    std::cout << "3, 친구 만나기 삽입" << std::endl;
    todos.insert(Todo(3, "친구 만나기"));
    std::cout << "2, 영화 보기 삽입" << std::endl;
    todos.insert(Todo(2, "영화 보기"));

    print_set(todos);

    std::cout << "--------------" << std::endl;
    std::cout << "숙제를 끝냈다면!" << std::endl;
    todos.erase(todos.find(Todo(2, "수학 숙제 하기")));
    print_set(todos);
}