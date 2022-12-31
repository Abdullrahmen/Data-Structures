#ifndef DOUBLY_LL_H_
#define DOUBLY_LL_H_

#include <memory>
#include <initializer_list>
#include <iostream>
using uint = unsigned long;

namespace _DoublyLL
{
    template<typename T>
    class Node
    {
    private:
        std::unique_ptr<Node<T>> _next;
        std::unique_ptr<T> _value;
        Node<T>* _previous;
    public:
        /// @brief Empty constructor
        Node();

        Node(const T &value);

        Node(T &&value);

        /// @brief Copy constructor, Warning: This will copy the stored value only.
        Node(const Node &node);

        /// @brief Move constructor
        Node(Node &&node);

        std::unique_ptr<T>& value();
        std::unique_ptr<Node<T>>& next();
        Node<T>* previous();
    };
}

template<typename T>
class DoublyLinkedList
{
private:
    std::unique_ptr<_DoublyLL::Node<T>> _head;
    _DoublyLL::Node<T>* _tail;
    uint _size;

    _DoublyLL::Node<T>* get_node(long long n);
public:
    DoublyLinkedList(/* args */);
    ~DoublyLinkedList();
};


#include "Doubly LL.tpp"
#endif //DOUBLY_LL_H_