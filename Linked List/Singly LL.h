#ifndef SINGLY_LL_H_
#define SINGLY_LL_H_

#include <memory>
#include <initializer_list>
#include <iostream>
using uint = unsigned long;

namespace _SinglyLL
{
    template<typename T>
    class Node
    {
    private:
        std::unique_ptr<T> _value; 
        std::unique_ptr<Node<T>> _next;
    public:
        /// @brief Empty constructor
        Node();

        Node(const T && value);
        //Node(T && value);

        /// @brief Copy constructor, Warning: This will copy the stored value only.
        Node(const Node& node);

        /// @brief Move constructor 
        Node(Node&& node);

        std::unique_ptr<T>& value();
        std::unique_ptr<Node<T>>& next();
    };
}
using namespace _SinglyLL;

template<typename T>
class SinglyLinkedList
{
private:
    std::unique_ptr<Node<T>> _head;
    Node<T>* _tail;
    uint _size;
public:
    /// @brief Empty constructor
    SinglyLinkedList();

    /// @brief Copy constructor
    SinglyLinkedList(const SinglyLinkedList& lst);

    /// @brief Move constructor
    SinglyLinkedList(SinglyLinkedList&& lst);

    /// @brief Initializer list constructor
    SinglyLinkedList(std::initializer_list<T> lst);

    void debug_print() const;

    ~SinglyLinkedList();
};

#include "Singly LL.tpp"
#endif //SINGLY_LL_H_