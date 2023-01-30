template <class T>
inline SparseMat<T>::SparseMat(const S_C &size, T &&default_value) : _size(size),
                                                                     _default_value(default_value)
{
    //if (_size.dimensions() == 1)
    {
        //head = std::make_unique<LL<Node<T>>>(nullptr);
        // this->heads= NULL;
    }
}
