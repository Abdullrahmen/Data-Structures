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

template<typename T> _DoublyLL::Node<T>* _DoublyLL::Node<T>::previous()
{return _previous;}

/// Finish Node class
/// Start DoublyLinkedList class

