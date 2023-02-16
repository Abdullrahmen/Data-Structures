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
BinaryTree<T>::Node::Node(const Node &node) : _value(std::make_unique<T>(*(node._value.get()))),
                                              _left(std::make_unique<Node>(*(node._left.get()))),
                                              _right(std::make_unique<Node>(*(node._right.get()))) {}

template <typename T>
BinaryTree<T>::Node::Node(Node &&node) : _value(std::move(node._value)),
                                         _left(std::move(node._left)),
                                         _right(std::move(node._right)) {}

template <typename T>
BinaryTree<T>::BinaryTree() : _root(nullptr),
                              _level(0)
{
    std::cout << "Empty constructor called.\n";
}

template <typename T>
BinaryTree<T>::BinaryTree(const BinaryTree &binary_tree) : // This will copy the entire tree (Node copy construction recursion)
                                                           _root(std::make_unique<Node>(*(binary_tree._root.get()))),
                                                           _level(binary_tree._level)
{
    std::cout << "Copy constructor called.\n";
}

template <typename T>
BinaryTree<T>::BinaryTree(BinaryTree &&binary_tree) : _root(std::move(binary_tree._root)),
                                                      _level(binary_tree._level)
{
    std::cout << "Move constructor called.\n";
}

template <typename T>
std::unique_ptr<typename BinaryTree<T>::Node> &BinaryTree<T>::get_node_from_path(std::initializer_list<char> node_path)
{
    // Before start change anything check the node_path
    for (auto &&i : node_path)
        if (i != 'L' && i != 'l' && i != 'R' && i != 'r')
            return nullptr;

    if (node_path.size() > _level)
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
        return current_node->_left;
    else
        return current_node->_right;
}

template <typename T>
bool BinaryTree<T>::add(std::initializer_list<char> value_path, const T &value)
{
    auto current_node{get_node_from_path(value_path)};
    if (!current_node)
        return false;

    current_node->_value = std::make_unique<T>(value);
    return true;
}

template <typename T>
bool BinaryTree<T>::add(std::initializer_list<char> value_path, T &&value)
{
    auto current_node{get_node_from_path(value_path)};
    if (!current_node)
        return false;

    current_node->_value = std::make_unique<T>(std::move(value));
    return true;
}

template <typename T>
bool BinaryTree<T>::remove(std::initializer_list<char> value_path)
{
    auto current_node{get_node_from_path(value_path)};
    if (!current_node)
        return false;

    current_node.reset(nullptr);
    return true;
}

template <typename T>
int BinaryTree<T>::get_level() const
{
    return _level;
}

template <typename T>
void BinaryTree<T>::_to_preorder_string(std::string (*type_converter_func)(const T &),
                                        std::string &append_in_str, const BinaryTree<T>::Node *const node,
                                        const std::string &null_nodes_string)
{
    if (!node)
    {
        append_in_str.append(null_nodes_string);
        return;
    }
    if (type_converter_func)
        append_in_str.append(type_converter_func(*node->_value.get()));
    else
        append_in_str.append(static_cast<std::string>(*node->_value.get()));
    
    _to_preorder_string(append_in_str, node->_left.get(), null_nodes_string);
    _to_preorder_string(append_in_str, node->_right.get(), null_nodes_string);
}

template <typename T>
std::string BinaryTree<T>::to_preorder_string(std::string (*type_converter_func)(const T &),
                                              const std::string &null_nodes_string)
{
    std::string preorder_str{};
    _to_preorder_string(type_converter_func, preorder_str, _root, null_nodes_string);
    return preorder_str;
}