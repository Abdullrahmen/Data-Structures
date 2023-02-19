#include "Queue.h"

void test1()
{
    Queue<int> q1{};

    q1.set_maximum_size(3);
    q1.enqueue(1);
    q1.enqueue(2);
    q1.debug_print();
    std::cout << "\n" << *q1.dequeue()<<"\n";
    q1.debug_print();
    std::cout << "\n\n";

    Queue<int> q2{q1};
    q2.enqueue(3);
    auto x{4};
    q2.enqueue(x);
    q2.debug_print();

    std::cout << "\n\n";
    Queue<int> q3{std::move(q2)};
}