#include "Singly LL.h"
#include <assert.h>

/// @brief Test all constructors
void test1()
{
    SinglyLinkedList<int>&& lst{1,2,3,4,5,6,7};
    lst.push_back(8);

    SinglyLinkedList<int> lst2{std::move(lst)};
    assert(lst2.get_size()==8);

    lst2.push_back(9);
    assert(lst2.get_size()==9);

    SinglyLinkedList<int> lst3{lst2};
    lst3.push_back(10);
    assert(lst3.get_size()==10);

    SinglyLinkedList<int> lst4{};
    lst4.push_back(1);
    assert(lst4.get_size()==1);

    std::cout<<"Test1 passed"<<"\n";
    //lst2.debug_print();
    //lst3.debug_print();
}

/// @brief Test push_back
void test2()
{
    SinglyLinkedList<int> lst{1};
    lst.push_back({2,3,4,5});
    assert(lst.get_size()==5);
    
    lst.push_back(6);
    assert(lst.get_size()==6);

    lst.push_back(10, -1);
    assert(lst.get_size()==16);

    //lst.debug_print();
    std::cout<<"Test2 passed"<<"\n";
}

/// @brief Test [] operator, drop_back
void test3()
{
    SinglyLinkedList<int> lst{1,2,3,4,5,6,7};
    lst.drop_back();
    assert(lst.get_size()==6);

    lst.drop_back(3);

    lst.debug_print();
    std::cout<<"Test3 passed"<<"\n";
}