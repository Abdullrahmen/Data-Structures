template <typename T>
BinaryTree<T>::Node::Node() : _value(nullptr),
                              _left(nullptr),
                              _right(nullptr) {}

template <typename T>
BinaryTree<T>::Node::Node(const T &value) : _value(std::make_unique<T>(value)),
                                            _left(nullptr),
                                            _right(nullptr) {}

template <typename T>
BinaryTree<T>::Node::Node(T &&value) : _value(std::make_unique<T>(std::move(value))),
                                       _left(nullptr),
                                       _right(nullptr) {}

template <typename T>
BinaryTree<T>::Node::Node(const Node &node) : _value(node._value.get() ? std::make_unique<T>(*(node._value.get())) : nullptr),
                                              _left(node._left.get() ? std::make_unique<Node>(*(node._left.get())) : nullptr),
                                              _right(node._right.get() ? std::make_unique<Node>(*(node._right.get())) : nullptr)
{
    //std::cout << "Node copied\n";
}

template <typename T>
BinaryTree<T>::Node::Node(Node &&node) : _value(std::move(node._value)),
                                         _left(std::move(node._left)),
                                         _right(std::move(node._right)) {}

template <typename T>
BinaryTree<T>::BinaryTree() : _root(std::make_unique<Node>(Node{})),
                              _level(1)
{
    //std::cout << "Empty constructor called.\n";
}

template <typename T>
BinaryTree<T>::BinaryTree(const BinaryTree &binary_tree) : // This will copy the entire tree (Node copy construction recursion)
                                                           _root(std::make_unique<Node>(*(binary_tree._root.get()))),
                                                           _level(binary_tree._level)
{
    //std::cout << "Copy constructor called.\n";
}

template <typename T>
BinaryTree<T>::BinaryTree(BinaryTree &&binary_tree) : _root(std::move(binary_tree._root)),
                                                      _level(binary_tree._level)
{
    //std::cout << "Move constructor called.\n";
}

template <typename T>
std::unique_ptr<typename BinaryTree<T>::Node> &BinaryTree<T>::get_node_from_path(std::initializer_list<char> node_path)
{
    if (node_path.size() == 0)
        return _root;

    // Before start change anything check the node_path
    for (auto &&i : node_path)
        if (i != 'L' && i != 'l' && i != 'R' && i != 'r')
            throw std::invalid_argument("invalid path.");

    if (node_path.size() >= _level)
        _level = node_path.size() + 1;

    Node *current_node{_root.get()};
    auto lst_iter{node_path.begin()};
    for (int i = 0; i < node_path.size() - 1; ++lst_iter, ++i) //-1 to get the unique pointer from parent node
    {
        if (*lst_iter == 'L' || *lst_iter == 'l')
        {
            if (!current_node->_left.get())
                current_node->_left = std::make_unique<Node>(Node{});
            current_node = current_node->_left.get();
        }
        else
        {
            if (!current_node->_right.get())
                current_node->_right = std::make_unique<Node>(Node{});
            current_node = current_node->_right.get();
        }
    }

    if (*lst_iter == 'L' || *lst_iter == 'l')
    {
        if (!current_node->_left.get())
            current_node->_left = std::make_unique<Node>(Node{});
        return current_node->_left;
    }
    else
    {
        if (!current_node->_right.get())
            current_node->_right = std::make_unique<Node>(Node{});
        return current_node->_right;
    }
}

template <typename T>
void BinaryTree<T>::add(std::initializer_list<char> value_path, const T &value)
{
    auto &current_node{get_node_from_path(value_path)};
    current_node->_value = std::make_unique<T>(value);
}

template <typename T>
void BinaryTree<T>::add(std::initializer_list<char> value_path, T &&value)
{
    auto &current_node{get_node_from_path(value_path)};
    current_node->_value = std::make_unique<T>(std::move(value));
}

template <typename T>
void BinaryTree<T>::remove(std::initializer_list<char> value_path)
{
    auto &current_node{get_node_from_path(value_path)};
    current_node.reset(nullptr);
}

template <typename T>
int BinaryTree<T>::get_level() const
{
    return _level;
}

template <typename T>
void BinaryTree<T>::_to_preorder_string(std::string (*type_converter_func)(const T &),
                                        std::string &append_in_str, const BinaryTree<T>::Node *const node,
                                        const std::string &null_nodes_string,
                                        const std::string &delim)
{
    if (!node)
    {
        append_in_str.append(null_nodes_string);
        append_in_str.append(delim);
        return;
    }

    if (type_converter_func != nullptr)
        append_in_str.append(type_converter_func(*node->_value.get()));
    else
    {
        try
        {
            append_in_str.append(std::to_string(*node->_value.get()));
        }
        catch (const std::exception &e)
        {
            throw e;
        }
    }

    append_in_str.append(delim);
    _to_preorder_string(type_converter_func, append_in_str, node->_left.get(), null_nodes_string, delim);
    _to_preorder_string(type_converter_func, append_in_str, node->_right.get(), null_nodes_string, delim);
}

template <typename T>
std::string BinaryTree<T>::to_preorder_string(std::string (*type_converter_func)(const T &),
                                              const std::string &null_nodes_string,
                                              const std::string &delim)
{
    std::string preorder_str{};
    _to_preorder_string(type_converter_func, preorder_str, _root.get(), null_nodes_string, delim);
    if (preorder_str.size())
        preorder_str.pop_back();
    return preorder_str;
}