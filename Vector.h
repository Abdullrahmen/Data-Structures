#ifndef Vector_H_
#define Vector_H_

//#include<memory>
#include<initializer_list>
#include<iostream>
#define DEFAULT_INITIAL_CAPACITY_SIZE 100
#define DEFAULT_MULTIPLICATION_FACTOR 2.0
#define DEFAULT_SUM_FACTOR 100
#define DEFAULT_CAPACITY_METHOD MULTIPLICATION
#define DEFAULT_CONSTRUCTION_METHOD LIST
using uint = unsigned long;

/// @brief Expand the capacity method
enum CAPACITY_METHOD {MULTIPLICATION, SUM};

uint floor(double&& v)
{
    if(v>=0)
        return uint(v);
    else
        return uint(v)-1;
}
uint floor(double& v)
{
    if(v>=0)
        return uint(v);
    else
        return uint(v)-1;
}

/// @brief 
/// @tparam T Copy constructor and = operator needed
template<typename T>
class Vector
{
private:
    uint _size;
    CAPACITY_METHOD _capacity_method;
    double _multiplication_factor;
    uint _sum_factor;
    uint _initial_capacity_size;
    uint _capacity_size;
    T* _vec;

    void expand_capacity(uint expand_to);
public:
    /// @brief Empty constructor
    Vector();

    /// @brief Copy constructor
    Vector(const Vector& vec);

    /// @brief Move constructor
    Vector(Vector&& vec);

    Vector(std::initializer_list<T> vec);

    /// made initializer_list constructor instead
    //template<typename ...E>
    //Vector(E &&... vec);
    
    /// @brief Eg. v.fill{50, false} -> Add 50 elements and filled with false.
    /// @param n Number of elements added and filled with value
    /// @param value
    void fill(uint n, T && value);

    /// @brief Add an element at the end of the vector
    /// @param value 
    void push_back(T && value);

    /// @brief Remove last item from the vector -Warning this won't reassign or delete the value immediately except if the capacity rescaled 
    /// @param rescale_capacity Rescale capacity if the capacity method conditions applied
    void drop_back(bool rescale_capacity= true);

    void debug_print() const;

    const uint get_size() const;
    const uint get_capacity_size() const;

    /// @brief First capacity size
    const uint get_initial_capacity_size() const;
    /// @param initial_capacity_size First capacity size
    void set_initial_capacity_size(uint initial_capacity_size);

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