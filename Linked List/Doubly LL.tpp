/// Start Node class

template <typename T> _DoublyLL::Node<T>::Node() :
_value(nullptr),
_next(nullptr),
_previous(nullptr)
{}

template <typename T> _DoublyLL::Node<T>::Node(const T& value):
_value(std::make_unique<T>(value)),
_next(nullptr),
_previous(nullptr)
{}

template <typename T> _DoublyLL::Node<T>::Node(T&& value):
_value(std::make_unique<T>(std::move(value))),
_next(nullptr),
_previous(nullptr)
{}

template <typename T> _DoublyLL::Node<T>::Node(const Node &node):
_value(std::make_unique<T>(*(node._value.get()))), //Copy node._value to _value
_next(nullptr),
_previous(nullptr)
{}

template <typename T> _DoublyLL::Node<T>::Node(Node &&node):
_value(std::move(node._value)),
_next(std::move(node._next)),
_previous(node._previous)
{node._previous=nullptr;}

template<typename T> std::unique_ptr<T>& _DoublyLL::Node<T>::value()
{return _value;}

template<typename T> std::unique_ptr<_DoublyLL::Node<T>>& _DoublyLL::Node<T>::next()
{return _next;}

template<typename T> _DoublyLL::Node<T>*& _DoublyLL::Node<T>::previous()
{return _previous;}

/// Finish Node class
/// Start DoublyLinkedList class

template<typename T> DoublyLinkedList<T>::DoublyLinkedList():
_head(nullptr),
_tail(nullptr),
_size(0)
{
    //std::cout<<"Empty constructor called"<<"\n";
}

template<typename T> DoublyLinkedList<T>::DoublyLinkedList(const DoublyLinkedList &lst):
_head(nullptr),
_tail(nullptr),
_size(0)
{
    //std::cout<<"Copy constructor called"<<"\n";

    if(!lst._size)
        return;

    _DoublyLL::Node<T> *itr{lst._head.get()};
    _DoublyLL::Node<T> *tmp_previous{nullptr};
    _head= std::make_unique<_DoublyLL::Node<T>>(*itr); // copy head node
    _tail= _head.get();
    ++_size;

    for (; _size < lst._size; ++_size)
    {
        itr= itr->next().get();
        _tail->next()= std::make_unique<_DoublyLL::Node<T>>(*itr);//copy next node
        tmp_previous= _tail; //store previous pointer
        _tail = _tail->next().get();
        _tail->previous()= tmp_previous; //pass previous pointer
    }
}

template<typename T> DoublyLinkedList<T>::DoublyLinkedList(DoublyLinkedList &&lst):
_head(std::move(lst._head)),
_tail(lst._tail),
_size(lst._size)
{
    //std::cout<<"Move constructor called."<<"\n";
}

template<typename T> DoublyLinkedList<T>::DoublyLinkedList(std::initializer_list<T> &&lst):
_head(nullptr),
_tail(nullptr),
_size(0)
{
    //std::cout<<"\n"<<"initializer_list called"<<"\n";

    if(!lst.size())
        return;

    auto j{lst.begin()};
    _head = std::make_unique<_DoublyLL::Node<T>>(*j);
    _DoublyLL::Node<T> *tmp_previous{nullptr};
    _tail = _head.get();
    ++_size;

    for (; _size < lst.size(); ++_size)
    {
        ++j;
        _tail->next() = std::make_unique<_DoublyLL::Node<T>>(*j); // create next node
        tmp_previous = _tail;   // store previous pointer
        _tail = _tail->next().get();
        _tail->previous() = tmp_previous; // pass previous pointer
    }
} 

template<typename T> _DoublyLL::Node<T>* DoublyLinkedList<T>::get_node(long long n)
{
    if (n < 0)
        n = _size + n;

    if (n == _size - 1)
        return _tail;
    
    if (n == 0)
        return _head.get();

    if(n <= 0 || n >= _size)
        throw(std::out_of_range("OOR"));

    /// @bug for debugging
    _debug_get_node_counter_=0;

    _DoublyLL::Node<T> *itr{nullptr};
    if(n < _size/2) //Loop from _head
    {
        itr= _head.get();
        for (int i = 0; i < n; i++)
        {
            itr = itr->_next.get();

            /// @bug for debugging
            ++_debug_get_node_counter_;
        }
    }
    else //Loop from _tail
    {
        itr= _tail;
        for (int i = 0; i < _size-n; i++)
        {
            itr= itr->_previous;

            /// @bug for debugging
            ++_debug_get_node_counter_;
        }
    }
    return itr;
}

template<typename T> void DoublyLinkedList<T>::push_back(const T& value)
{
    if(!_size)
    {
        initialize_head_tail(value);
        ++_size;
        return;
    }

    _DoublyLL::Node<T> *tmp_previous{_tail};
    _tail->next() = std::make_unique<_DoublyLL::Node<T>>(value);
    _tail= _tail->next().get();
    _tail->previous()= tmp_previous;
    ++_size;
}
template<typename T> void DoublyLinkedList<T>::push_back(T&& value)
{
    if(!_size)
    {
        initialize_head_tail(std::move(value));
        ++_size;
        return;
    }

    _DoublyLL::Node<T> *tmp_previous{_tail};
    _tail->next() = std::make_unique<_DoublyLL::Node<T>>(std::move(value));
    _tail = _tail->next().get();
    _tail->previous()= tmp_previous;
    ++_size;
}
template<typename T> void DoublyLinkedList<T>::push_back(std::initializer_list<T> &&lst)
{
    if (!lst.size())
        return;

    auto tmp_size= _size + lst.size(); 

    auto j{lst.begin()};
    if(!_size)
    {
        initialize_head_tail(*j);
        ++_size;
        ++j;
    }
    
    _DoublyLL::Node<T> *tmp_previous{nullptr};
    for (; _size < tmp_size; ++_size, ++j)
    {
        _tail->next()= std::make_unique<_DoublyLL::Node<T>>(*j);
        tmp_previous= _tail;
        _tail= _tail->next();
        _tail->previous= tmp_previous;
    }
}
template<typename T> void DoublyLinkedList<T>::push_back(uint n, T &&value)
{
    if(!n)
        return;

    auto tmp_size= _size + n;

    if(!_size)
    {
        initialize_head_tail(std::move(value));
        ++_size;
    }

    _DoublyLL::Node<T> *tmp_previous{nullptr};
    for (; _size < tmp_size; ++_size)
    {
        _tail->next()= std::make_unique<_DoublyLL::Node<T>>(std::move(value));
        tmp_previous= _tail;
        _tail= _tail->next();
        _tail->previous= tmp_previous;
    }
}
template<typename T> void DoublyLinkedList<T>::push_back(uint n, const T &value)
{
    if(!n)
        return;

    auto tmp_size= _size + n;

    if(!_size)
    {
        initialize_head_tail(value);
        ++_size;
    }

    _DoublyLL::Node<T> *tmp_previous{nullptr};
    for (; _size < tmp_size; ++_size)
    {
        _tail->next()= std::make_unique<_DoublyLL::Node<T>>(value);
        tmp_previous= _tail;
        _tail= _tail->next();
        _tail->previous= tmp_previous;
    }
}

template<typename T> void DoublyLinkedList<T>::initialize_head_tail(T &&value)
{
    if(_head.get())
        return;
    
    _head= std::make_unique<_DoublyLL::Node<T>>(_DoublyLL::Node<T>{std::move(value)});
    _tail= _head.get();
}
template<typename T> void DoublyLinkedList<T>::initialize_head_tail(const T &value)
{
    if(_head.get())
        return;

    _head= std::make_unique<_DoublyLL::Node<T>>(_DoublyLL::Node<T>{value});
    _tail= _head.get();
}

template<typename T> T& DoublyLinkedList<T>::operator[] (long long n)
{
    return *(get_node(n)->value().get());
}

template<typename T> uint DoublyLinkedList<T>::get_size() const
{
    return _size;
}

template<typename T> void DoublyLinkedList<T>::debug_print() const
{
    _DoublyLL::Node<T>* itr{_head.get()};
    std::cout<<"\n"<<_size<<"\n";
    for (int i = 0; i < _size; i++)
    {
        std::cout<<*(itr->value())<<"\t";
        itr= itr->next().get();
    }
}

template<typename T> DoublyLinkedList<T>::~DoublyLinkedList()
{}

