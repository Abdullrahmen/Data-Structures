#include "Binary Tree.h"
#include <assert.h>

std::string int2str(const int &i)
{
    // std::cout<<"int2str called\n";
    return std::to_string(i);
}

/// @brief test everything.
void test1()
{
    BinaryTree<int> binary_tree1{};
    binary_tree1.add({}, 1);
    binary_tree1.add({'L'}, 2);
    auto x{3};
    binary_tree1.add({'R'}, x);

    BinaryTree<int> binary_tree2{binary_tree1};
    binary_tree2.remove({'R'});
    binary_tree2.add({'L', 'L'}, 3);

    auto preorder{binary_tree1.to_preorder_string(int2str, "-1", " ")};
    assert(std::string("1 2 -1 -1 3 -1 -1") == preorder);

    preorder = binary_tree2.to_preorder_string(int2str, "-1", " ");
    assert(std::string("1 2 3 -1 -1 -1 -1") == preorder);

    BinaryTree<int> &&binary_tree3{};
    BinaryTree<int> binary_tree4{std::move(binary_tree3)};
    binary_tree4.add({}, 1);
    binary_tree4.add({'L'}, 2);
    binary_tree4.add({'L', 'R'}, 3);
    preorder = binary_tree4.to_preorder_string(int2str, "-1", " ");
    assert(std::string("1 2 -1 3 -1 -1 -1") == preorder);

    assert(binary_tree1.get_level() == 2);
    assert(binary_tree2.get_level() == 3);
    assert(binary_tree4.get_level() == 3);
}