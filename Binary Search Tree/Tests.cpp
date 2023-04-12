#include "BinarySearchTree.h"

void test1()
{
    // Balanced
    //Vector<int> v{0};
    //Vector<int> v{0, 1, 2};
    //Vector<int> v{0, 1, 2, 3, 4, 5, 6};
    //Vector<int> v{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14};
    Vector<int> v{0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30};
    
    // unBalanced
    //Vector<int> v{0, 1, 2, 3, 4};
    //Vector<int> v{0, 1, 2, 3, 4, 5};
    Vector<int> v2{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19};

    BinarySearchTree<int> b{v, false, false};
}