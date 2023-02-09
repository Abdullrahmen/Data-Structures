
template <typename T>
Stack<T>::Stack() : _tail{nullptr},
                    _size(0) {}

template <typename T>
Stack<T>::Stack(const Stack &stack) : _tail(nullptr),
                                      _size(0)
{
    if (!stack._size)
        return;

    Node<T> *iter{stack._tail.get()};                        // iterator over stack elements
    _tail = std::make_unique<Node<T>>(*iter->value().get()); // copy tail
    Node<T> *head_iter{_tail.get()};                         // iterator to copy from iter to this stack
    ++_size;

    for (; _size < stack._size; ++_size)
    {
        iter = iter->next().get();
        head_iter->next() = std::make_unique<Node<T>>(*iter->value().get());
        head_iter = head_iter->next().get();
    }
}

template <typename T>
Stack<T>::Stack(Stack &&stack) : _tail(std::move(stack._tail)),
                                 _size(stack._size) {}

template <typename T>
void Stack<T>::clear()
{
    _tail.reset(nullptr);
    _size = 0;
}

template <typename T>
std::unique_ptr<T> Stack<T>::drop_back()
{
    if (!_size)
        return nullptr;

    std::unique_ptr<T> last_value = std::move(_tail->value()); // move last value

    _tail = std::move(_tail->next()); // move previous node to _tail

    --_size;
    return std::move(last_value);
}

template <typename T>
void Stack<T>::push_back(const T &value)
{
    auto temp_next{std::move(_tail)};
    _tail = std::make_unique<Node<T>>(value);
    _tail->next() = std::move(temp_next);
    ++_size;
}
template <typename T>
void Stack<T>::push_back(T &&value)
{
    auto temp_next{std::move(_tail)};
    _tail = std::make_unique<Node<T>>(std::move(value));
    _tail->next() = std::move(temp_next);
    ++_size;
}

template <class T>
void Stack<T>::debug_print(std::string delim) const
{
    if (!_size)
        return;
    Node<T> *iter{_tail.get()};
    std::cout << *iter->value().get() << delim;
    for (int i = 1; i < _size; ++i)
    {
        iter = iter->next().get();
        std::cout << *iter->value().get() << delim;
    }
}
