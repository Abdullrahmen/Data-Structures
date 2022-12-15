/// Start Node class

template<typename T> Node<T>::Node():
_value(nullptr),
_next(nullptr)
{}

template<typename T> Node<T>::Node(const T&& value):
_value(std::make_unique<T>(value)),
_next(nullptr)
{}

template<typename T> Node<T>::Node(const Node& node):
_value(std::make_unique<T>(*(node._value.get()))), //Copy node._value to _value
_next(nullptr)
{}

template<typename T> Node<T>::Node(Node&& node):
_value(std::move(node._value)),
_next(std::move(node._next))
{}

template<typename T> std::unique_ptr<T>& Node<T>::value()
{return _value;}

template<typename T> std::unique_ptr<Node<T>>& Node<T>::next()
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
    std::cout<<"\n"<<"copy constructor called"<<"\n";

    if(_size)
    {
        Node<T>* tmp_itr1 = lst._head.get();
        _head= std::make_unique<Node<T>>(*tmp_itr1); //copy head node.
        Node<T>* tmp_itr2= _head.get();

        for (int i = 1; i < _size; i++)
        {
            tmp_itr1= tmp_itr1->next().get();
            tmp_itr2->next()= std::make_unique<Node<T>>(*tmp_itr1); //copy next node.
            tmp_itr2= tmp_itr2->next().get();
        }
        _tail= tmp_itr2;
    }
}

template<typename T> SinglyLinkedList<T>::SinglyLinkedList(std::initializer_list<T> lst):
_head(nullptr),
_tail(nullptr),
_size(lst.size())
{
    std::cout<<"\n"<<"initializer_list called"<<"\n";
    
    if(lst.size())
    {
        auto j{lst.begin()};
        _head= std::make_unique<Node<T>>(Node<T>{std::move(*j)}); //copy first value to new head node.
        Node<T>* tmp_itr= _head.get();
        ++j;

        for (int i = 1; i < _size; i++,++j)
        {
            tmp_itr->next()= std::make_unique<Node<T>>(Node<T>{std::move(*j)});
            tmp_itr= tmp_itr->next().get();
        }
        _tail= tmp_itr;
    }
}

template<typename T> void SinglyLinkedList<T>::debug_print() const
{
    Node<T>* tmp{_head.get()};
    std::cout<<"\n"<<_size<<"\n";
    for (int i = 0; i < _size; i++)
    {
        std::cout<<*(tmp->value())<<"\t";
        tmp= tmp->next().get();
    }
}

template<typename T> SinglyLinkedList<T>::~SinglyLinkedList()
{}