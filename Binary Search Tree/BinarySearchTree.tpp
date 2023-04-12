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
BinarySearchTree<T>::BinarySearchTree(const Vector<T> &vector, bool is_sorted, bool is_without_duplicates) : _root(nullptr),
                                                                                                             _level(0)
{
    if (!vector.get_size())
        return;

    /// sorted vector without duplicates
    Vector<std::unique_ptr<Node>> sorted_vector{};

    sorted_vector.set_minimal_capacity_size(vector.get_size()); // expand the capacity to the size of the vector

    if (is_without_duplicates)
        for (int i = 0; i < vector.get_size(); ++i)
            sorted_vector.push_back(std::make_unique<Node>(vector[i]));
    else
    {
        // remove duplicates with this way till Vector class support drop method ( O(n^2) )
        for (int i = 0; i < vector.get_size(); ++i)
        {
            bool is_duplicated = false;
            for (int j = 0; j < sorted_vector.get_size(); ++j)
                if (*sorted_vector[j]->_value == vector[i])
                {
                    is_duplicated = true;
                    break;
                }
            if (!is_duplicated)
                sorted_vector.push_back(std::make_unique<Node>(vector[i]));
        }

        sorted_vector.set_minimal_capacity_size(1); // minimize the capacity
    }

    if (!is_sorted)
        sort_vector(sorted_vector);

    /*For debug*/
    for (int i = 0; i < sorted_vector.get_size(); i++)
        std::cout << std::to_string(*sorted_vector[i]->_value) << " ";
    std::cout<<"\n";

    unsigned int n_items_to_add{0};
    unsigned int n_items_in_balanced{1};
    unsigned int vec_size{sorted_vector.get_size()};
    unsigned int counter{1};
    while (true)
        if (vec_size < n_items_in_balanced)
        {
            n_items_in_balanced -= n_items_to_add;
            break;
        }
        else
        {
            n_items_to_add = 1;
            for (int i = 0; i < counter; i++)
                n_items_to_add *= 2;

            n_items_in_balanced += n_items_to_add;
            ++counter;
        }

    n_items_to_add = vec_size - n_items_in_balanced;
    if (!n_items_to_add)
        init_from_balanced_vector(sorted_vector);
    else
    {
        // Fully balanced vector
        Vector<std::unique_ptr<Node>> balanced_vector{};

        /// items to add to the tree after init from balanced vector
        Vector<std::unique_ptr<Node>> added_vector{};

        Vector<int> items_to_add{};
        int sum_factor{std::ceil(vec_size / double(n_items_to_add))};
        for (int i = vec_size - 1; i > 0; i -= sum_factor)
            items_to_add.push_back(i);

        /*for debug*/
        std::cout << "\n";
        for (int i = 0; i < items_to_add.get_size(); i++)
            std::cout << items_to_add[i] << "  " ;
        std::cout<<"\n";

        for (int i = 0; i < vec_size; i++)
            if (i == items_to_add[-1])
            {
                added_vector.push_back(std::move(sorted_vector[i]));
                items_to_add.drop_back(1, false);
            }
            else
                balanced_vector.push_back(std::move(sorted_vector[i]));

        init_from_balanced_vector(balanced_vector);

        for (int i = 0; i < added_vector.get_size(); i++)
            add_node(added_vector[i]);
    }

    debug_print();
}
template <typename T>
BinarySearchTree<T>::BinarySearchTree(Vector<T> &&vector, bool is_sorted, bool is_without_duplicates)
{
}

template <class T>
void BinarySearchTree<T>::add_node(std::unique_ptr<BinarySearchTree<T>::Node> &node_to_add)
{
    Node *node{_root.get()};
    unsigned int this_level{1};
    while (true)
    {
        ++this_level;
        if (*node_to_add->_value < *node->_value)
            if (node->_left)
                node = node->_left.get();
            else
            {
                node_to_add->_parent = node;
                node->_left = std::move(node_to_add);
                if (this_level > _level)
                    _level = this_level;
                break;
            }
        else if (*node_to_add->_value > *node->_value)
            if (node->_right)
                node = node->_right.get();
            else
            {
                node_to_add->_parent = node;
                node->_right = std::move(node_to_add);
                if (this_level > _level)
                    _level = this_level;
                break;
            }
        else
            throw std::invalid_argument("Tried to add a duplicate value to the tree");
    }
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
unsigned int BinarySearchTree<T>::get_level() const
{
    return _level;
}

template <class T>
unsigned int BinarySearchTree<T>::auto_rebalance(BinarySearchTree<T>::Node &node)
{
}

template <class T>
void BinarySearchTree<T>::sort_vector(Vector<std::unique_ptr<Node>> &vector)
{
    // Bubble sort (Temp) O(n^2)

    bool is_sorted = false;
    while (!is_sorted)
    {
        is_sorted = true;
        for (int i = 0; i < vector.get_size() - 1; ++i)
            if (*vector[i + 1]->_value < *vector[i]->_value)
            {
                is_sorted = false;
                swap_node(vector[i + 1], vector[i]); // swap
            }
    }
}

template <class T>
void BinarySearchTree<T>::debug_print() const
{
    std::cout << "\n\nLevels: " << _level<< "\n";
    Node *to_print_node{_root.get()};
    std::string n_tabs{};
    for (int i = 0; i < _level; i++)
        n_tabs.append(" ");
    std::string str{};
    str.append("\n");
    str.append(n_tabs);
    str.append(" ");
    str.append(std::to_string(*to_print_node->_value));
    str.append("\n");

    for (int this_level = 1; this_level < _level; ++this_level)
    {
        int l{n_tabs.length()};
        // for (int i = 0; i < this_level; i++)
        l /= 2;

        for (int i = 0; i < l; i++)
            n_tabs.pop_back();

        // l = n_tabs.length();
        // for (int i = 0; i < l/ 2; i++)
        // n_tabs.pop_back();

        bool is_left{true};
        to_print_node = _root.get();
        bool is_empty{false};

        int n_nodes_in_this_level{1};
        for (int i = 0; i < this_level; i++)
            n_nodes_in_this_level *= 2;

        for (int i = 0; i < n_nodes_in_this_level; i++)
        {
            double level_i{i};
            for (int j = 0; j < this_level; j++)
                level_i /= 2;
            while (to_print_node->_parent)
                to_print_node = to_print_node->_parent;

            is_empty = false;
            for (int j = 0; j < this_level; j++)
            {
                level_i *= 2;
                is_left = (int(std::floor(level_i)) % 2) == 0;

                if (is_left)
                {
                    if (!to_print_node->_left)
                    {
                        is_empty = true;
                        break;
                    }
                    to_print_node = to_print_node->_left.get();
                }
                else
                {
                    if (!to_print_node->_right)
                    {
                        is_empty = true;
                        break;
                    }
                    to_print_node = to_print_node->_right.get();
                }
            }
            if (!is_empty)
            {
                str.append(n_tabs);
                str.append(std::to_string(*to_print_node->_value));
                str.append(n_tabs);
            }
            else
            {
                str.append(n_tabs);
                str.append("NULL");
                str.append(n_tabs);
            }
            // std::cout<<str;
            // std::cout<<"\n\n";
        }
        str.append("\n");
    }
    str.append("\n\n\n");
    std::cout << str;
}

template <class T>
void BinarySearchTree<T>::init_from_balanced_vector(Vector<std::unique_ptr<BinarySearchTree<T>::Node>> &balanced_vec)
{
    unsigned int start{0};
    unsigned int end{balanced_vec.get_size() - 1};
    Vector<unsigned int> middle{};
    middle.set_minimal_capacity_size(balanced_vec.get_size());
    // middle.push_back(0);
    middle.push_back(end + 1);
    middle.push_back(end / 2);

    _root = std::move(balanced_vec[middle[-1]]);
    _level = 1;
    Node *node = &(*_root);
    //std::cout << std::to_string(*node->_value);
    //std::cout << "\n";
    Node *parent_node(nullptr);

    // debug_print();

    unsigned int this_level{1};
    while (middle[-1] != balanced_vec.get_size() - 1)
    {
        if (middle[-1] != start)
            end = middle[-1] - 1;
        else
        {
            int counter{1};
            for (; counter < middle.get_size(); ++counter)
            {
                if (end == middle[-counter - 1] - 1)
                    break;
            }

            middle.drop_back(counter, false);
            for (int i = 0; i < counter; i++)
                node = &(*node->_parent);
            start = middle[-1] + 1;

            for (int i = 2; i < middle.get_size() + 1; i++)
            {
                if (end < middle[-i])
                {
                    end = middle[-i] - 1;
                    break;
                }
            }

            if (this_level > _level)
                _level = this_level;
            this_level -= counter;
        }
        middle.push_back((end + start) / 2);

        parent_node = &*node;
        //std::cout << std::to_string(start) << std::to_string(end) << "\t" << std::to_string(middle[-1]) << std::to_string(middle[-2]) << std::to_string(middle[-3]);
        if (middle[-1] < middle[-2])
        {
            node->_left = std::move(balanced_vec[middle[-1]]);
            node = &(*node->_left);
        }
        else
        {
            node->_right = std::move(balanced_vec[middle[-1]]);
            node = &(*node->_right);
        }
        ++this_level;
        //std::cout << "\t" << std::to_string(*node->_value);
        //std::cout << "\n";
        node->_parent = parent_node;
    }
}