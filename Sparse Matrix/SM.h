//Uses Linked List to create general(multitype) multidimensional Sparse Matrix.
#ifndef GSM_H_
#define GSM_H_
#include "../Linked List/Singly LL.h"
#include "../Vector/Vector.h"
#include <memory>
#include <initializer_list>
#include <iostream>
#include <variant>

using uint = unsigned long;

/// Default Linked List
#define LL SinglyLinkedList


/// @brief Size or coordinates
struct S_C
{
    Vector<int> _s_c;
    
    S_C(const Vector<int>& s_c):
    _s_c(s_c)
    {
        _s_c.set_sum_factor(1);
        _s_c.set_capacity_method(SUM);
        _s_c.set_minimal_capacity_size(1);
    }
    int dimensions()
    {
        return _s_c.get_size();
    }
};

namespace _SparseMat_
{
    /// @brief Contains the item and its real coordinates
    template <typename T>
    class Node
    {
    private:
        /* data */
    public:
        Node(/* args */);
        ~Node();
    };
}
using namespace _SparseMat_;

/// @brief General (multitype) sparse matrix -> can overload to make numbers matrix
/// @tparam T Matrix items' type -> eg. int
template<typename T>
class SparseMat
{
private:
    S_C _size;

    T _default_value;

    //Up to 5D Sparse Matrix (Look at the UML to understand -_-)
    std::variant <Node<T>,
        LL<std::variant<Node<T>,
        LL<std::variant<Node<T>,
        LL<std::variant<Node<T>,
        LL<std::variant<Node<T>>>>>>>>>>* _head;


public:
    /// @brief Empty constructor
    SparseMat();

    /// @brief Copy constructor
    SparseMat(const SparseMat<T> &mat);

    /// @brief Move constructor
    SparseMat(SparseMat<T> &&mat);

    /// @brief Constructor
    /// @param size Size of matrix
    /// @param default_value Default (Filled) value
    SparseMat(const S_C &size, const T &default_value);
    SparseMat(const S_C &size, T &&default_value);

    void set_value(const S_C &coord, const T &value);
    void set_value(const S_C &coord, T &&value);

    void reset_value(const S_C &coord)
    {
        this->head.get();
    }

    ~SparseMat();
};
#include "SM.tpp"
#endif // SM_H_
