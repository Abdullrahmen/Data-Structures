/*
Linked list based stack
*/

#ifndef STACK_H_
#define STACK_H_

#include <iostream>
#include <memory>
#include "../Linked List/Singly LL.h"
using uint = unsigned long;
using namespace _SinglyLL; //Singly linked list Node

template<typename T>
class Stack
{
private:
    std::unique_ptr<Node<T>> _head;
    uint _size;
    
public:
    Stack();
    ~Stack();
};

#include "Stack.tpp"
#endif // STACK_H_