template <typename T>
BinarySearchTree<T>::Node::Node() : _value(nullptr),
                                    _left(nullptr),
                                    _right(nullptr),
                                    _parent(nullptr) {}

template <typename T>
BinarySearchTree<T>::Node::Node(const T &value) : _value(std::make_unique<T>(value)),
                                                  _left(nullptr),
                                                  _right(nullptr),
                                                  _parent(nullptr) {}

template <typename T>
BinarySearchTree<T>::Node::Node(T &&value) : _value(std::make_unique<T>(std::move(value))),
                                             _left(nullptr),
                                             _right(nullptr),
                                             _parent(nullptr) {}

template <typename T>
BinarySearchTree<T>::Node::Node(const Node &node) : _value(node._value.get() ? std::make_unique<T>(*(node._value.get())) : nullptr),
                                                    _left(node._left.get() ? std::make_unique<Node>(*(node._left.get())) : nullptr),
                                                    _right(node._right.get() ? std::make_unique<Node>(*(node._right.get())) : nullptr),
                                                    _parent(node._parent)
{
    // std::cout << "Node copied\n";
}

template <typename T>
BinarySearchTree<T>::Node::Node(Node &&node) : _value(std::move(node._value)),
                                               _left(std::move(node._left)),
                                               _right(std::move(node._right)),
                                               _parent(node._parent) {}

template <typename T>
BinarySearchTree<T>::BinarySearchTree(const T &value) : _level(0),
                                                        _root(std::make_unique<Node>(value))
{
    if (_root)
        _level = 1;
}
template <typename T>
BinarySearchTree<T>::BinarySearchTree(T &&value) : _level(0),
                                                   _root(std::make_unique<Node>(std::move(value)))
{
    if (_root)
        _level = 1;
}
template <typename T>
BinarySearchTree<T>::BinarySearchTree(const BinarySearchTree &search_tree) : _level(search_tree._level),
                                                                             _root(search_tree._root.get() ? std::make_unique<Node>(*(search_tree._root.get())) : nullptr)
{
}
template <typename T>
BinarySearchTree<T>::BinarySearchTree(BinarySearchTree &&search_tree) : _level(search_tree._level),
                                                                        _root(std::move(search_tree._root))
{
}
template <typename T>
BinarySearchTree<T>::BinarySearchTree(const Vector<T> &vector, bool is_sorted, bool is_without_duplicates)
{
    Vector<std::unique_ptr<T>> sorted_vector{};
    sorted_vector.set_minimal_capacity_size(vector.get_size()); // expand the capacity to the size of the vector

    if (is_without_duplicates)
        for (int i = 0; i < vector.get_size(); ++i)
            sorted_vector.push_back(std::make_unique<T>(vector[i]));
    else
    {
        // remove duplicates with this way till Vector class support drop method ( O(n^2) )
        for (int i = 0; i < vector.get_size(); ++i)
        {
            bool is_duplicated = false;
            for (int j = 0; j < sorted_vector.get_size(); ++j)
                if (*sorted_vector[j] == vector[i])
                {
                    is_duplicated = true;
                    break;
                }
            if (!is_duplicated)
                sorted_vector.push_back(std::make_unique<T>(vector[i]));
        }

        sorted_vector.set_minimal_capacity_size(1); // minimize the capacity
    }
    
    if (!is_sorted)
        sort_vector(sorted_vector);

    for (int i = 0; i < sorted_vector.get_size(); i++)
    {
        std::cout << std::to_string(*sorted_vector[i]) << " ";
    }
}
template <typename T>
BinarySearchTree<T>::BinarySearchTree(Vector<T> &&vector, bool is_sorted, bool is_without_duplicates)
{
}

template <typename T>
void BinarySearchTree<T>::add(const T &value)
{
}
template <typename T>
void BinarySearchTree<T>::add(T &&value)
{
}

template <typename T>
bool BinarySearchTree<T>::search(const T &search_value) const
{
    return false;
}

template <typename T>
bool BinarySearchTree<T>::remove(const T &value)
{
    return false;
}

template <typename T>
Vector<T> BinarySearchTree<T>::move_to_sorted_vector()
{
    return Vector<T>();
}

template <typename T>
Vector<T> BinarySearchTree<T>::copy_to_sorted_vector() const
{
    return Vector<T>();
}

template <class T>
int BinarySearchTree<T>::get_level() const
{
    return _level;
}

template <class T>
int BinarySearchTree<T>::auto_rebalance(BinarySearchTree<T>::Node &node)
{
}

template <class T>
void BinarySearchTree<T>::sort_vector(Vector<std::unique_ptr<T>> &vector)
{
    // Bubble sort (Temp) O(n^2)

    bool is_sorted = false;
    while (!is_sorted)
    {
        is_sorted = true;
        for (int i = 0; i < vector.get_size() - 1; ++i)
            if (*vector[i + 1] < *vector[i])
            {
                is_sorted = false;
                swap(vector[i + 1], vector[i]); // swap
            }
    }
}
