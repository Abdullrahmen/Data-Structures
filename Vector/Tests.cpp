#include "Vector.h"
#include <iostream>
#include <assert.h>
/// @brief Test SUM method + initializer_list constructor
void test1()
{   
    auto z{"4"};
    auto x{"5"};
    auto y{"6"};
    auto a{"7"};
    Vector<std::string> v{"1","2","3",x,z};

    v.set_sum_factor(3);
    v.set_capacity_method(SUM);
    assert(v.get_capacity_size()==DEFAULT_MINIMAL_CAPACITY_SIZE);

    v.set_minimal_capacity_size(3);
    assert(v.get_capacity_size()==7);

    v.push_back(y);
    v.push_back(std::move(a));
    assert(v.get_capacity_size()==7);

    v.push_back("6");
    assert(v.get_capacity_size()==10);
    
    std::cout<<"Test1 passed"<<"\n";

}

/// @brief Test MULTIPLICATION method + initializer_list constructor
void test2()
{
    Vector<int> v{1};
    v.set_multiplication_factor(2);
    assert(v.get_capacity_size()==DEFAULT_MINIMAL_CAPACITY_SIZE);

    v.set_minimal_capacity_size(2);
    assert(v.get_capacity_size()==2);

    v.set_capacity_method(MULTIPLICATION);
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);
    assert(v.get_capacity_size()==4);

    v.push_back(5);
    assert(v.get_capacity_size()==8);
    
    std::cout<<"Test2 passed"<<"\n";
}

/// @brief Test move, copy constructors
void test3()
{
    Vector<bool>&& v{Vector<bool>{false,true,false}};
    v.push_back(false);
    Vector<bool> v2{std::move(v)};
    assert(v.get_capacity_size()==0);
    assert(v2.get_size()==4);

    Vector<bool> v3{v2};
    v3.push_back(false);
    assert(v2.get_size()==4);
    assert(v3.get_size()==5);

    std::cout<<"Test3 passed"<<"\n";
}

/// @brief Test drop_back, push_back
void test4()
{
    Vector<int> v{1};
    v.set_sum_factor(3);
    v.set_minimal_capacity_size(5);
    v.set_capacity_method(SUM);

    v.push_back({2,3,4,5,6});
    assert(v.get_capacity_size() == 8);

    v.push_back({7,8});
    v.push_back(9);
    assert(v.get_capacity_size() == 11);

    v.push_back(50, -1);
    assert(v.get_capacity_size() == 59);

    v.drop_back(50, true);
    assert(v.get_capacity_size() == 11);

    v.push_back(50, -1);
    assert(v.get_capacity_size() == 59);

    v.drop_back(50, false);
    assert(v.get_capacity_size() == 59);

    std::cout<<"Test4 passed"<<"\n";
    //v.debug_print();
}

/// @brief Test [] operator
void test5()
{
    Vector<int> v{1};
    v.set_sum_factor(3);
    v.set_minimal_capacity_size(5);
    v.set_capacity_method(SUM);

    v.push_back({2,3,4,5,6});
    v[-2] =-1;
    v[3] =-2;

    assert(v[0]==1);
    assert(v[-1]==6);
    assert(v[-2]==-1);
    assert(v[2]==3);
    assert(v[3]==-2);


    //std::cout<<v[-6];
    //v.debug_print();

    std::cout<<"Test5 passed"<<"\n";
}