/// Start Node class

template<typename T> _SinglyLL::Node<T>::Node():
_value(nullptr),
_next(nullptr)
{}

template<typename T> _SinglyLL::Node<T>::Node(const T& value):
_value(std::make_unique<T>(value)),
_next(nullptr)
{}

template<typename T> _SinglyLL::Node<T>::Node(T&& value):
_value(std::make_unique<T>(std::move(value))),
_next(nullptr)
{}

template<typename T> _SinglyLL::Node<T>::Node(const Node& node):
_value(std::make_unique<T>(*(node._value.get()))), //Copy node._value to _value
_next(nullptr)
{}

template<typename T> _SinglyLL::Node<T>::Node(Node&& node):
_value(std::move(node._value)),
_next(std::move(node._next))
{}

template<typename T> std::unique_ptr<T>& _SinglyLL::Node<T>::value()
{return _value;}

template<typename T> std::unique_ptr<_SinglyLL::Node<T>>& _SinglyLL::Node<T>::next()
{return _next;}

/// Finish Node class
/// Start SinglyLinkedList class

template<typename T> SinglyLinkedList<T>::SinglyLinkedList():
_head(nullptr),
_tail(nullptr),
_size(0)
{}

template<typename T> SinglyLinkedList<T>::SinglyLinkedList(const SinglyLinkedList& lst):
_head(nullptr), 
_tail(nullptr),
_size(lst._size)
{
    //std::cout<<"\n"<<"copy constructor called"<<"\n";

    if(_size)
    {
        _SinglyLL::Node<T>* tmp_itr1 = lst._head.get();
        _head= std::make_unique<_SinglyLL::Node<T>>(*tmp_itr1); //copy head node.
        _tail= _head.get();

        for (int i = 1; i < _size; i++)
        {
            tmp_itr1= tmp_itr1->next().get();
            _tail->next() = std::make_unique<_SinglyLL::Node<T>>(*tmp_itr1); // copy next node.
            _tail = _tail->next().get();
        }
    }
}

template<typename T> SinglyLinkedList<T>::SinglyLinkedList(SinglyLinkedList&& lst):
_head(std::move(lst._head)), 
_tail(std::move(lst._tail)),
_size(lst._size)
{
    lst._size=0;
    //std::cout<<"\n"<<"move constructor called"<<"\n";
}

template<typename T> SinglyLinkedList<T>::SinglyLinkedList(std::initializer_list<T>&& lst):
_head(nullptr),
_tail(nullptr),
_size(lst.size())
{
    //std::cout<<"\n"<<"initializer_list called"<<"\n";
    
    if(lst.size())
    {
        auto j{lst.begin()};
        initialize_head_tail(std::move(*j)); //copy first value to new head node.
        _tail= _head.get();
        ++j;

        for (int i = 1; i < lst.size(); i++,++j)
        {
            _tail->next()= std::make_unique<_SinglyLL::Node<T>>(_SinglyLL::Node<T>{std::move(*j)});
            _tail= _tail->next().get();
        }
    }
}

template<typename T> void SinglyLinkedList<T>::initialize_head_tail(T&& value)
{
    if(!_head.get())
    {
        _head= std::make_unique<_SinglyLL::Node<T>>(_SinglyLL::Node<T>{std::move(value)});
        _tail= _head.get();
    }
}
template <typename T> void SinglyLinkedList<T>::initialize_head_tail(const T &value)
{
    if (!_head.get())
    {
        _head = std::make_unique<_SinglyLL::Node<T>>(_SinglyLL::Node<T>{value});
        _tail = _head.get();
    }
}

template<typename T> void SinglyLinkedList<T>::push_back(const T & value)
{
    if (_size)
    {
        _tail->next() = std::make_unique<_SinglyLL::Node<T>>(_SinglyLL::Node<T>{value});
        _tail = _tail->next().get();
        ++_size;
    }
    else
    {
        initialize_head_tail(value);
        ++_size;
    }
}
template<typename T> void SinglyLinkedList<T>::push_back(T && value)
{
    if(_size)
    {
        _tail->next()= std::make_unique<_SinglyLL::Node<T>>(_SinglyLL::Node<T>{std::move(value)});
        _tail= _tail->next().get();
        ++_size;
    }
    else
    {
        initialize_head_tail(std::move(value));
        ++_size;
    }
}
template<typename T> void SinglyLinkedList<T>::push_back(std::initializer_list<T>&& lst)
{
    if(!lst.size())
        return;

    if(_size)
    {
        for (auto &&i : lst)
        {
            _tail->next()= std::make_unique<_SinglyLL::Node<T>>(_SinglyLL::Node<T>{std::move(i)});
            _tail= _tail->next().get();
        }
        _size+= lst.size();
    }
    else
    {
        auto j{lst.begin()};
        initialize_head_tail(std::move(*j)); //copy first value to head node.
        _tail= _head.get();
        ++j;

        for (int i = 1; i < lst.size(); i++,++j)
        {
            _tail->next()= std::make_unique<_SinglyLL::Node<T>>(_SinglyLL::Node<T>{std::move(*j)});
            _tail= _tail->next().get();
        }
        _size+= lst.size();
    }
}
template<typename T> void SinglyLinkedList<T>::push_back(uint n, T && value)
{
    if(n==0)
        return;

    push_back(std::move(value)); //to initialize _head and _tail if they didn't.
    for (int i = 1; i < n; i++)
    {
        _tail->next()= std::make_unique<_SinglyLL::Node<T>>(_SinglyLL::Node<T>{std::move(value)});
        _tail= _tail->next().get();
    }
    _size+= n-1; //-1 because push_back above already increase _size by 1 
}
template<typename T> void SinglyLinkedList<T>::push_back(uint n, const T & value)
{
    if(n==0)
        return;

    push_back(value); //to initialize _head and _tail if they didn't.
    for (int i = 1; i < n; i++)
    {
        _tail->next()= std::make_unique<_SinglyLL::Node<T>>(_SinglyLL::Node<T>{value});
        _tail= _tail->next().get();
    }
    _size+= n-1; //-1 because push_back above already increase _size by 1 
}

template<typename T> void SinglyLinkedList<T>::drop_back(uint n)
{
    if(n>=_size)
    {
        _tail= nullptr;
        _head.reset(); //will delete all items in the list
        _size= 0;
    }
    else
    {
        _tail= get_node(-static_cast<long long>(n)-1); //-1 to remove ownership from the previous node
        _tail->next().reset(); //this will delete any node next to this node
        _size-= n;
    }
}

template<typename T> _SinglyLL::Node<T>* SinglyLinkedList<T>::get_node(long long n)
{    
    if(n < 0)
        n= _size+n;

    if(n==_size-1)
        return _tail;
    else if (n==0)
        return _head.get();
    
    if(n > 0 && n < _size)
    {
        _SinglyLL::Node<T>* itr{_head.get()};
        for (int i = 0; i < n; i++)
            itr= itr->next().get();

        return itr;
    }
    throw(std::out_of_range("OOR"));
}

template<typename T> T& SinglyLinkedList<T>::operator[] (long long n)
{
    return *(get_node(n)->value().get());
}

template<typename T> uint SinglyLinkedList<T>::get_size() const
{
    return _size;
}

template<typename T> void SinglyLinkedList<T>::debug_print() const
{
    _SinglyLL::Node<T>* tmp{_head.get()};
    std::cout<<"\n"<<_size<<"\n";
    for (int i = 0; i < _size; i++)
    {
        std::cout<<*(tmp->value())<<"\t";
        tmp= tmp->next().get();
    }
}

template<typename T> SinglyLinkedList<T>::~SinglyLinkedList()
{}