#include "Singly LL.h"
#include "Doubly LL.h"
#include <assert.h>

/// @brief Test all constructors
void s_test1()
{
    // Initializer list constructor
    SinglyLinkedList<int> lst{1, 2, 3, 4, 5, 6, 7};
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

/// @brief Test all constructors
void d_test1()
{
    // Initializer list constructor
    DoublyLinkedList<int> lst{1, 2, 3, 4, 5, 6, 7};
    lst.push_back(8);

    // Move constructor
    DoublyLinkedList<int> lst2{std::move(lst)};
    
    assert(lst2.get_size() == 8);

    lst2.push_back(9);
    assert(lst2.get_size() == 9);

    // Copy constructor
    DoublyLinkedList<int> lst3{lst2};
    lst3.push_back(10);
    assert(lst3.get_size() == 10);

    // Empty constructor
    DoublyLinkedList<int> lst4{};
    lst4.push_back(1);
    assert(lst4.get_size() == 1);

    std::cout << "d_Test1 passed"<< "\n";
    // lst3.debug_print();
}

/// @brief Test push_back
void d_test2()
{
    DoublyLinkedList<int> lst{1};
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
    std::cout<<"d_Test2 passed"<<"\n";
}

/// @brief Test [] operator and drop_back
void d_test3()
{
    DoublyLinkedList<int> lst{1, 2, 3, 4, 5, 6, 7};
    lst.drop_back();
    assert(lst.get_size() == 6);
    lst.drop_back(3);
    assert(lst.get_size() == 3);

    assert(lst[0] == 1);
    assert(lst[1] == 2);
    assert(lst._debug_get_node_counter_==1);
    assert(lst[-1] == 3);

    auto x{4};
    lst[0] = 4;
    lst[1] = 5;
    assert(lst._debug_get_node_counter_==1);
    lst[-1] = 6;
    assert(lst[0] == 4);
    assert(lst[1] == 5);
    assert(lst[-1] == 6);
    assert(lst[2] == 6);
    lst.push_back({1,2,3,4,5});
    assert(lst[-2] == 4);
    assert(lst._debug_get_node_counter_== 1);
    assert(lst[-4] == 2);
    assert(lst._debug_get_node_counter_ == 3);
    assert(lst[-5] == 1);
    assert(lst._debug_get_node_counter_ == 3);
    assert(lst[-6] == 6);
    assert(lst._debug_get_node_counter_ == 2);

    lst.drop_back(10);
    assert(lst.get_size() == 0);

    // lst.debug_print();
    std::cout << "d_Test3 passed"<< "\n";
}
