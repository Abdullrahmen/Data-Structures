#ifndef Vector_H_
#define Vector_H_

#include<memory>
#include<initializer_list>
#include<iostream>
#include<cmath>
#define DEFAULT_MINIMAL_CAPACITY_SIZE 100
#define DEFAULT_MULTIPLICATION_FACTOR 2.0
#define DEFAULT_SUM_FACTOR 100
#define DEFAULT_CAPACITY_METHOD MULTIPLICATION
#define DEFAULT_CONSTRUCTION_METHOD LIST
using uint = unsigned long;

/// @brief Expand the capacity method
enum CAPACITY_METHOD {MULTIPLICATION, SUM};

/// @brief 
/// @tparam T Copy constructor and = operator required
template<typename T>
class Vector
{
private:
    uint _size;
    CAPACITY_METHOD _capacity_method;
    double _multiplication_factor;
    uint _sum_factor;
    uint _minimal_capacity_size;
    uint _capacity_size;
    std::unique_ptr<T[]> _vec;
    //T* _vec; changed to smart pointers

    void expand_capacity(uint expand_to);
public:
    /// @brief Empty constructor
    Vector();

    /// @brief Copy constructor
    Vector(const Vector& vec);

    /// @brief Move constructor
    Vector(Vector&& vec);

    /// @brief Initializer list constructor
    Vector(std::initializer_list<T>&& lst);

    /// @todo
    void right_rotate(int times);
    void left_rotate(int times);
    T& pop(uint idx);
    uint find_transposition(T && value);

    /// @brief Add elements at the end of the vector 
    /// @note Eg. v.push_back(false) -> Add false at the end of the vector.
    /// @note Eg. v.push_back({true, true, false}) -> Add 3 elements (true, true, false) at the end of the vector.
    /// @note Eg. v.push_back(50, false) -> Add 50 elements filled with false.
    void push_back(T && value);
    void push_back(std::initializer_list<T>&& lst);
    void push_back(uint n, T && value);

    /// @todo 
    void push_back(const Vector<T> & vec);
    void push_back(const Vector<T> && vec);
    void operator=( Vector<T> & vec);
    void operator=( Vector<T> && vec);

    /// @brief Remove last n items from the vector -Warning this won't reassign or delete the values except if the capacity rescaled 
    /// @param n drop last n items, If n >= vector size -> will delete all items in the vector.
    /// @param rescale_capacity Rescale capacity if the capacity method conditions applied
    void drop_back(int n=1, bool rescale_capacity= true);

    void debug_print() const;

    const uint get_size() const;
    const uint get_capacity_size() const;

    /// @brief First capacity size
    const uint get_minimal_capacity_size() const;
    /// @param minimal_capacity_size First capacity size
    void set_minimal_capacity_size(uint minimal_capacity_size);

    /// @brief capacity_method Expand the capacity method
    const CAPACITY_METHOD get_capacity_method() const;
    /// @param capacity_method Expand the capacity method
    void set_capacity_method(CAPACITY_METHOD method);

    /// @brief Expand the capacity with multiplication factor * -> Needed capacity_method == MULTIPLICATION
    const double get_multiplication_factor() const;
    /// @param multiplication_factor Expand the capacity with multiplication factor * -> Needed capacity_method == MULTIPLICATION
    void set_multiplication_factor(double factor);
    
    /// @brief Expand the capacity with sum factor * -> Needed capacity_method == SUM
    const uint get_sum_factor() const;
    /// @param sum_factor Expand the capacity with sum factor * -> Needed capacity_method == SUM
    void set_sum_factor(uint factor);

    ~Vector();
};

#include "Vector.tpp"

#endif //Vector_H_