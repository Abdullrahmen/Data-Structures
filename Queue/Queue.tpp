template <typename T>
Queue<T>::Queue(uint size) : _maximum_size(0),
                             _actual_size(0),
                             _values(nullptr),
                             _head(0),
                             _tail(0)
{
    set_maximum_size(size);
}

template <typename T>
Queue<T>::Queue(const Queue &queue) : _maximum_size(0),
                                      _actual_size(queue._actual_size),
                                      _values(nullptr),
                                      _head(queue._head),
                                      _tail(queue._tail)
{
    if (!queue._maximum_size)
        return;

    set_maximum_size(queue._maximum_size);

    if (!_actual_size)
        return;

    auto copy_idx{_head};
    for (int i = 0; i < _actual_size; ++i)
    {
        // copy from queue._values array to this _value array
        (*_values)[copy_idx] = std::make_unique<T>(*((*(queue._values))[copy_idx].get()));

        // increment the copy idx
        copy_idx = get_next_idx(copy_idx);
    }
}

template <typename T>
Queue<T>::Queue(Queue &&queue) : _maximum_size(queue._maximum_size),
                                 _actual_size(queue._actual_size),
                                 _values(std::move(queue._values)),
                                 _head(queue._head),
                                 _tail(queue._tail)
{
}

template <typename T>
void Queue<T>::set_maximum_size(const uint &maximum_size)
{
    if (_maximum_size) // check if already specified _maximum_size
        throw std::invalid_argument("Already specified maximum queue size");

    if (!maximum_size) // check argument
        throw std::invalid_argument("The maximum size can't be 0");

    _values = std::make_unique<std::unique_ptr<T>[]>(_maximum_size);
}

template <typename T>
void Queue<T>::enqueue(const T &value)
{
    if (is_full())
        throw std::invalid_argument("The queue is full.\ncan't enqueue other elements.");

    (*_values)[_tail] = std::make_unique<T>(value);
    _tail = get_next_idx(_tail);
    ++_actual_size;
}

template <typename T>
void Queue<T>::enqueue(T &&value)
{
    if (is_full())
        throw std::invalid_argument("The queue is full.\ncan't enqueue other elements.");

    (*_values)[_tail] = std::make_unique<T>(std::move(value));
    _tail = get_next_idx(_tail);
    ++_actual_size;
}

template <typename T>
std::unique_ptr<T> Queue<T>::dequeue()
{
    if (is_empty())
        throw std::invalid_argument("The queue is empty.\ncan't dequeue elements.");

    auto first_value = std::move((*_values)[_head]);
    _head = get_next_idx(_head);
    --_actual_size;

    return std::move(first_value);
}
