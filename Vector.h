#ifndef Vector_H_
#define Vector_H_

#include<memory>
#include<initializer_list>
#include<iostream>
#define DEFAULT_INITIAL_CAPACITY_SIZE 3
#define DEFAULT_MULTIPLICATION_FACTOR 2
#define DEFAULT_SUM_FACTOR 5
#define DEFAULT_CAPACITY_METHOD MULTIPLICATION
#define DEFAULT_CONSTRUCTION_METHOD LIST

/// @brief Expand the capacity method
enum CAPACITY_METHOD {MULTIPLICATION, SUM};

enum CONSTRUCTION_METHOD {FILLED_VALUE, LIST};

template<typename T> 
class Vector
{
private:
    int _size;
    CAPACITY_METHOD _capacity_method;
    int _multiplication_factor;
    int _sum_factor;
    int _initial_capacity_size;
    int _capacity_size;
    T* _vec;

    /// @param expand_to 
    void expand_capacity(int expand_to);
public:
    /// @brief Empty constructor
    Vector();

    /// @param C Copy constructor and = assignment operator needed.
    template<typename ...E>
    Vector(E &&... vec);
    
    /// @brief Eg. v.fill{50, false} -> Add 50 elements and filled with false.
    /// @param n Number of elements added and filled with value
    /// @param value
    void fill(int n, T && value);

    void push_back(T && value);

    void change_capacity_settings(int initial_capacity_size= DEFAULT_INITIAL_CAPACITY_SIZE,
        CAPACITY_METHOD capacity_method= MULTIPLICATION,
        int multiplication_factor=DEFAULT_MULTIPLICATION_FACTOR,
        int sum_factor=DEFAULT_SUM_FACTOR);

    void print() const;

    int get_size() const;
    int get_capacity_size() const;

    /// @brief First capacity size
    int get_initial_capacity_size() const;
    /// @param initial_capacity_size First capacity size
    void set_initial_capacity_size(int initial_capacity_size);

    /// @brief capacity_method Expand the capacity method
    CAPACITY_METHOD get_capacity_method() const;
    /// @param capacity_method Expand the capacity method
    void set_capacity_method(CAPACITY_METHOD method);

    /// @brief Expand the capacity with multiplication factor * -> Needed capacity_method == MULTIPLICATION
    int get_multiplication_factor() const;
    /// @param multiplication_factor Expand the capacity with multiplication factor * -> Needed capacity_method == MULTIPLICATION
    void set_multiplication_factor(int factor);
    
    /// @brief Expand the capacity with sum factor * -> Needed capacity_method == SUM
    int get_sum_factor() const;
    /// @param sum_factor Expand the capacity with sum factor * -> Needed capacity_method == SUM
    void set_sum_factor(int factor);

    ~Vector();
};

#include "Vector.tpp"

#endif //Vector_H_