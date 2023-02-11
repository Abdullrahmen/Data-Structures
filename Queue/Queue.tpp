template <typename T>
Queue<T>::Queue(uint size) : _maximum_size(0),
                             _actual_size(0),
                             _values(nullptr),
                             _head(0),
                             _tail(0)
{ set_maximum_size(size); }

template <typename T>
Queue<T>::Queue(const Queue &queue)
{
}

template <typename T>
Queue<T>::Queue(Queue &&queue) : _maximum_size(queue._maximum_size),
                                 _actual_size(queue._actual_size),
                                 _values(std::move(queue._values)),
                                 _head(queue._head),
                                 _tail(queue._tail)
{}

template <typename T>
void Queue<T>::set_maximum_size(const uint &maximum_size)
{
    if (_maximum_size != 0) //check if already specified _maximum_size
        throw std::invalid_argument("Already specified maximum queue size");

    if (maximum_size == 0) //check argument
        throw std::invalid_argument("The maximum size can't be 0");

    _values = std::make_unique<std::unique_ptr<T>[]>(_maximum_size);
}

template <typename T>
void Queue<T>::enqueue(const T &value)
{
}

template <typename T>
void Queue<T>::enqueue(T &&value)
{
}

template <typename T>
std::unique_ptr<T> Queue<T>::dequeue()
{
    return std::unique_ptr<T>();
}
