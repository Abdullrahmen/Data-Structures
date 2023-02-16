/*
Linked list based stack
*/

#ifndef STACK_H_
#define STACK_H_

#include <iostream>
#include <memory>
#include "../Linked List/Singly LL.h"
using uint = unsigned long;
using namespace _SinglyLL; // Singly linked list Node

/// @brief Stack based on linked list.
/// @tparam T
template <typename T>
class Stack
{
private:
    /*
    -- Stack doesn't contain any head pointer --
    ex.
    node <- node <- node <- node <- node
                                     |
                                    tail
    */

    /// @brief The tail of the stack
    std::unique_ptr<Node<T>> _tail;

    /// @brief The size of the stack
    uint _size;

public:
    /// @brief Empty constructor
    Stack();

    /// @brief Copy constructor
    Stack(const Stack &stack);

    /// @brief Move constructor
    Stack(Stack &&stack);

    /// @brief Clear the stack
    void clear();

    /// @brief pop last item of the stack
    /// @return A unique pointer to the last item or nullptr if the stack is empty
    /// @note O(1)
    [[nodiscard]] std::unique_ptr<T> drop_back();

    /// @brief Add value to the end of the stack
    /// @param value
    /// @note O(1)
    void push_back(const T &value);
    void push_back(T &&value);

    void debug_print(std::string delim = "  ") const;

    //~Stack();
};

#include "Stack.tpp"
#endif // STACK_H_