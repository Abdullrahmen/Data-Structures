#include "Singly LL.h"
#include "Doubly LL.h"
#include <assert.h>

/// @brief Test all constructors
void s_test1()
{
    // Initializer list constructor
    SinglyLinkedList<int>&& lst{1,2,3,4,5,6,7};
    lst.push_back(8);

    // Move constructor
    SinglyLinkedList<int> lst2{std::move(lst)};
    assert(lst2.get_size()==8);

    lst2.push_back(9);
    assert(lst2.get_size()==9);

    // Copy constructor
    SinglyLinkedList<int> lst3{lst2};
    lst3.push_back(10);
    assert(lst3.get_size()==10);

    // Empty constructor
    SinglyLinkedList<int> lst4{};
    lst4.push_back(1);
    assert(lst4.get_size()==1);

    std::cout<<"s_Test1 passed"<<"\n";
    //lst2.debug_print();
    //lst3.debug_print();
}

/// @brief Test push_back
void s_test2()
{
    SinglyLinkedList<int> lst{1};
    lst.push_back({2,3,4,5});
    assert(lst.get_size()==5);
    
    lst.push_back(6);
    assert(lst.get_size()==6);

    auto x{9};
    lst.push_back(x);
    assert(lst.get_size() == 7);

    lst.push_back(10, -1);
    assert(lst.get_size() == 17);

    lst.push_back(3, x);
    assert(lst.get_size() == 20);

    //lst.debug_print();
    std::cout<<"s_Test2 passed"<<"\n";
}

/// @brief Test [] operator and drop_back
void s_test3()
{
    SinglyLinkedList<int> lst{1,2,3,4,5,6,7};
    lst.drop_back();
    assert(lst.get_size() == 6);
    lst.drop_back(3);
    assert(lst.get_size() == 3);

    assert(lst[0] == 1);
    assert(lst[1] == 2);
    assert(lst[-1] == 3);

    auto x{4};
    lst[0] = 4;
    lst[1] = 5;
    lst[-1] = 6;
    assert(lst[0] == 4);
    assert(lst[1] == 5);
    assert(lst[-1] == 6);
    assert(lst[2] == 6);

    lst.drop_back(10);
    assert(lst.get_size() == 0);

    //lst.debug_print();
    std::cout<<"s_Test3 passed"<<"\n";
}

void d_test1()
{

}