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
        Node<T>*& previous();
    };
}

template<typename T>
class DoublyLinkedList
{
private:
    std::unique_ptr<_DoublyLL::Node<T>> _head;
    _DoublyLL::Node<T>* _tail;
    uint _size;

    /// @brief If _head is empty, will initialize it with value without increase _size
    void initialize_head_tail(T &&value);
    void initialize_head_tail(const T &value);

    _DoublyLL::Node<T>* get_node(long long n);
public:
    uint _debug_get_node_counter_{0};
    
    /// @brief Empty constructor
    DoublyLinkedList();

    /// @brief Copy constructor
    DoublyLinkedList(const DoublyLinkedList &lst);

    /// @brief Move constructor
    DoublyLinkedList(DoublyLinkedList &&lst);

    /// @brief Initializer list constructor
    DoublyLinkedList(std::initializer_list<T> &&lst);

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
    /// @param n drop last n items
    /// @note If n >= list size -> will delete all items in the list.
    void drop_back(uint n = 1);

    T &operator[](long long n);

    void debug_print() const;

    uint get_size() const;

    ~DoublyLinkedList();
};


#include "Doubly LL.tpp"
#endif //DOUBLY_LL_H_