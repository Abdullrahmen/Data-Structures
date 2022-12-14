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

        Node(const T & value);

        Node(T && value);

        /// @brief Copy constructor, Warning: This will copy the stored value only.
        Node(const Node& node);

        /// @brief Move constructor 
        Node(Node&& node);

        std::unique_ptr<T>& value();
        std::unique_ptr<Node<T>>& next();
    };
}

template<typename T>
class SinglyLinkedList
{
private:
    std::unique_ptr<_SinglyLL::Node<T>> _head;
    _SinglyLL::Node<T>* _tail;
    uint _size;

    /// @brief If _head is empty it will initialize it with value only without increase _size
    void initialize_head_tail(T &&value);
    void initialize_head_tail(const T &value);

    _SinglyLL::Node<T>* get_node(long long n);
public:
    /// @brief Empty constructor
    SinglyLinkedList();

    /// @brief Copy constructor
    SinglyLinkedList(const SinglyLinkedList& lst);

    /// @brief Move constructor
    SinglyLinkedList(SinglyLinkedList&& lst);

    /// @brief Initializer list constructor
    SinglyLinkedList(std::initializer_list<T>&& lst);

    /// @brief Add elements at the end of the list 
    /// @note Eg. lst.push_back(false) -> Add false at the end of the list.
    /// @note Eg. lst.push_back({true, true, false}) -> Add 3 elements (true, true, false) at the end of the list.
    /// @note Eg. lst.push_back(50, false) -> Add 50 elements filled with false.
    void push_back(const T &value);
    void push_back(T &&value);
    void push_back(std::initializer_list<T> &&lst);
    void push_back(uint n, T &&value);
    void push_back(uint n, const T &value);

    /// @brief Drop last n items from the list
    /// @param n drop last n items, If n >= list size -> will delete all items in the list.
    void drop_back(uint n=1);

    T& operator[] (long long n);

    void debug_print() const;

    uint get_size() const; 

    ~SinglyLinkedList();
};

#include "Singly LL.tpp"
#endif //SINGLY_LL_H_