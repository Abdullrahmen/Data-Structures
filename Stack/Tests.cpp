#include "Stack.h"

/// @brief Test constructors, push_back
void test1()
{
    Stack<int> stack1{};
    stack1.push_back(1);
    stack1.push_back(2);
    auto x{3};
    stack1.push_back(x);

    Stack<int> stack2{stack1};
    stack2.push_back(4);

    Stack<int> stack3{std::move(stack2)};

    std::cout << "First stack: ";
    stack1.debug_print();

    std::cout << "\nSecond stack: ";
    stack3.debug_print();

    std::cout << "\nTest1 Finished\n";
}

/// @brief Test drop_back, clear.
void test2()
{
    Stack<int> stack{};
    stack.push_back(1);
    stack.push_back(2);
    stack.push_back(3);

    auto x{stack.drop_back()};
    std::cout << "\nDropped item: " << *x.get();

    std::cout << "\nThe stack before clear: ";
    stack.debug_print();
    stack.clear();

    std::cout << "\nThe stack after clear: ";
    stack.debug_print();

    std::cout << "\nTest2 Finished\n";
}
