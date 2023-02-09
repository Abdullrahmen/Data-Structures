#include "Stack.h"

/// @brief Test constructors, push_back
void test1()
{
    Stack<int> stack1{};
    stack1.push_back(5);
    stack1.push_back(3);
    auto x{2};
    stack1.push_back(x);

    Stack<int> stack2{stack1};
    stack2.push_back(5);

    Stack<int>&& stack3{};
    Stack<int> stack4{std::move(stack3)};

    stack1.debug_print(" ");
    std::cout<<'\n';
    stack2.debug_print(" ");
}