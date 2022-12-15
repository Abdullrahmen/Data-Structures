#include "Singly LL.h"

void test1()
{
    SinglyLinkedList<int> lst{1,2,3,4,5,6,7};
    SinglyLinkedList<int> lst2{lst};

    lst.debug_print();
    lst2.debug_print();
}