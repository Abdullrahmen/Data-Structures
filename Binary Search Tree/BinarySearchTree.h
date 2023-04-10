/*
Efficient binary search tree (all methods' time complexity O(log(n)) except constructor+destructor+from_to_vector)
with auto rebalance option
*/
#ifndef BINARY_SEARCH_TREE_H_
#define BINARY_SEARCH_TREE_H_

#include <iostream>
#include <memory>
#include "../Vector/Vector.h" // from and to preorder vector

//Need get method to take the ownership from it.
//#include "../Linked List/Singly LL.h"


/// max degenerate nodes for auto rebalance
#define MAX_DEGENERATE_NODES 5

template <typename T>
class BinarySearchTree
{
private:
    struct Node
    {
        std::unique_ptr<Node> _left;
        std::unique_ptr<Node> _right;
        std::unique_ptr<T> _value;
        Node* _parent; //for simplicity
    };
    std::unique_ptr<Node> _root;
    int _level;
    //int max_degenerate_nodes; changed to global micro

    int _debug_number_of_search_iters;
    int _debug_number_of_add_iters;

    /// @brief auto rebalance a branch without check number of degenerated nodes >= MAX_DEGENERATE_NODES
    /// @param node Any node in the degenerated branch
    /// @return new number of levels
    /// @note Time complexity : O(m) where m is MAX_DEGENERATE_NODES
    int auto_rebalance(Node &node);

public:
    /// @brief Empty constructor
    BinarySearchTree();

    /// @brief Copy constructor
    BinarySearchTree(const BinarySearchTree& search_tree);

    /// @brief Move constructor
    BinarySearchTree(BinarySearchTree&& search_tree);

    /// @brief Copy from pre-order vector
    /// @param pre_order
    BinarySearchTree(const Vector<T> &pre_order);
    /// @brief Move from pre-order vector
    BinarySearchTree(Vector<T> &&pre_order);

    /// @brief Add a value to the tree with auto rebalance if the degenerated nodes > MAX_DEGENERATE_NODES
    /// @param value
    /// @note Time complexity : O(log(n)), n= number of tree elements
    void add(const T& value);
    void add(T&& value);

    /// @brief Search for a value in the tree
    /// @param search_value
    /// @return true if found
    /// @note Time complexity : O(log(n)), n= number of tree elements
    [[nodiscard]] bool search(const T &search_value);

    /// @todo
    /// @brief Search for a value in the tree
    /// @param search_value
    /// @return Path to search_value if found or [-1] if the value is the root else empty vector (where 0 is left and 1 is right)
    /// @note Time complexity : O(log(n)), n= number of tree elements
    //[[nodiscard]] Vector<int> search_and_get_path(const T &search_value);
    //[[nodiscard]] Vector<int> search_and_get_path(T &&search_value);

    /// @brief Remove a value in the tree
    /// @param value
    /// @return True if removed else false
    /// @note Time complexity : O(log(n)), n= number of tree elements
    bool remove(const T& value);

    /// @todo
    /// @param path the path of the value where 0 is left, 1 is right
    // bool remove(const Vector<int>& path);

    /// @todo
    /// @brief Manual rebalance method (auto rebalance)
    /// @return number of levels after rebalanced
    /// @note Time complexity : O(n)
    // int rebalance();

    /// @brief Move the binary search tree to a pre-order vector, Warning: this will clear the tree
    /// @return pre-order vector
    /// @note Time complexity : O(n), n= number of tree elements
    [[nodiscard]] Vector<T> move_to_preorder_vector(); // will clear the tree

    /// @brief Copy the binary search tree to a pre-order vector
    /// @return pre-order vector
    /// @note Time complexity : O(n), n= number of tree elements
    [[nodiscard]] Vector<T> copy_to_preorder_vector();

    //~BinarySearchTree(); //smart pointers
};

#include "BinarySearchTree.tpp"
#endif // BINARY_SEARCH_TREE_H_