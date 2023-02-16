/*
Multi-type general binary tree
*/
#ifndef BINARY_TREE_H_
#define BINARY_TREE_H_

#include <iostream>
#include <memory>
#include <initializer_list>

template <typename T>
class BinaryTree
{
private:
    struct Node
    {
        std::unique_ptr<T> _data;
        std::unique_ptr<Node> _left;
        std::unique_ptr<Node> _right;
    };
    /// @brief Root node
    std::unique_ptr<Node> _root;
    
    /// @brief The binary tree level
    int _level;

public:
    /// @brief Empty constructor
    BinaryTree();

    /// @brief Copy constructor
    BinaryTree(const BinaryTree &binary_tree);

    /// @brief Move constructor
    BinaryTree(BinaryTree &&binary_tree);

    /// @brief Add a value to the binary tree
    /// @param value_path The value path in the binary tree eg. {'L', 'R', 'L'} where 'L' is left and 'R' is right
    /// @param value The value added in the value_path
    /// @return true if successfully added
    bool add(std::initializer_list<char> value_path, const T &value);
    bool add(std::initializer_list<char> value_path, T &&value);

    /// @brief Remove a value in the binary tree
    /// @param value_path The value path in the binary tree eg. {'L', 'R', 'L'} where 'L' is left and 'R' is right
    /// @return true if successfully removed
    bool remove(std::initializer_list<char> value_path);

    /// @return The level of the binary tree
    int get_level() const;

    /// @brief Convert the binary tree to pre-order string, require T ability to convert to std::string
    /// @param type_converter_func optional, if it's null then will cast by static_cast< std::string >
    /// @return Pre-order string if succeed  or empty string
    std::string to_preorder_string(std::string (*type_converter_func)(const T &) = nullptr);
};

#include "Binary Tree.tpp"
#endif // BINARY_TREE_H_
