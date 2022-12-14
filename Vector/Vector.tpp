template<typename T> Vector<T>::Vector():
_minimal_capacity_size(DEFAULT_MINIMAL_CAPACITY_SIZE),
_capacity_method(DEFAULT_CAPACITY_METHOD),
_multiplication_factor(DEFAULT_MULTIPLICATION_FACTOR),
_sum_factor(DEFAULT_SUM_FACTOR),
_capacity_size(0),
_size(0),
_vec(nullptr){}

template<typename T> Vector<T>::Vector(const Vector& vec):
_minimal_capacity_size(vec._minimal_capacity_size),
_capacity_method(vec._capacity_method),
_multiplication_factor(vec._multiplication_factor),
_sum_factor(vec._sum_factor),
_capacity_size(vec._capacity_size),
_size(vec._size),
_vec(new T[_capacity_size])
{
    //std::cout<<"\n"<<"copy constructor called"<<"\n";

    for (uint i = 0; i < _size; i++)
        _vec[i] = vec._vec[i];
}

template<typename T> Vector<T>::Vector(Vector&& vec):
_minimal_capacity_size(vec._minimal_capacity_size),
_capacity_method(vec._capacity_method),
_multiplication_factor(vec._multiplication_factor),
_sum_factor(vec._sum_factor),
_capacity_size(vec._capacity_size),
_size(vec._size),
_vec(std::move(vec._vec))
{
    //std::cout<<"\n"<<"move constructor called"<<"\n";
    vec._capacity_size=0;
    vec._size=0;
    vec._vec= nullptr;
}

template<typename T> Vector<T>::Vector(std::initializer_list<T> lst):
_minimal_capacity_size(DEFAULT_MINIMAL_CAPACITY_SIZE),
_capacity_method(DEFAULT_CAPACITY_METHOD),
_multiplication_factor(DEFAULT_MULTIPLICATION_FACTOR),
_sum_factor(DEFAULT_SUM_FACTOR),
_capacity_size(0),
_size(0),
_vec(nullptr)
{
    //std::cout<<"\n"<<"initializer_list constructor called"<<"\n";
    if(lst.size()>0)
    {
        expand_capacity(lst.size());
        std::copy(lst.begin(),lst.end(),_vec.get());
        _size= lst.size();
    }
}

template<typename T> void Vector<T>::expand_capacity(uint expand_to)
{
    if(expand_to== _capacity_size)
        return;

    uint temp_capacity{_capacity_size};

    if (expand_to <= _minimal_capacity_size)
        temp_capacity = _minimal_capacity_size;    
    else
        switch (_capacity_method)
        {
        case MULTIPLICATION:
        {
            if(expand_to < temp_capacity)
            {
                while(true)
                {
                    if(uint(temp_capacity/_multiplication_factor) > expand_to && uint(temp_capacity/_multiplication_factor) > _minimal_capacity_size)
                        temp_capacity /= _multiplication_factor;
                    else
                        break;
                }
            }
            else
                while(temp_capacity < expand_to)
                    temp_capacity *= _multiplication_factor;
        }break;
        case SUM:
        {
            /// @brief SUM equation: capacity - factor * floor( double(capacity/factor) - double(expand_to/factor) )
            int f= std::floor(temp_capacity/double(_sum_factor)-expand_to/double(_sum_factor));
            auto t= temp_capacity-(_sum_factor * f);
            if(t <= _minimal_capacity_size)
                temp_capacity= _minimal_capacity_size;
            else
                temp_capacity= t;
        }break;
        default:
            throw std::invalid_argument("Unknown capacity method");
            break;
        }

    if(_capacity_size==temp_capacity) //the capacity is good
        return;
    _capacity_size= temp_capacity;

    //T* temp_vec= new T[_capacity_size]; //Changed to smart pointers
    std::unique_ptr<T[]> temp_vec {new T[_capacity_size]};
    for (uint i = 0; i < _size; i++)
        temp_vec[i]= _vec[i];

    std::swap(temp_vec, _vec);
    
    //if(temp_vec) //Changed to smart pointers
        //delete[] temp_vec;
}

template<typename T> void Vector<T>::push_back(T && value)
{
    if(_size+1 > _capacity_size)
        expand_capacity(_size+1);
    
    ++_size;
    _vec[_size-1]= value;
}
template<typename T> void Vector<T>::push_back(std::initializer_list<T> lst)
{
    if(_size + lst.size() > _capacity_size)
        expand_capacity(_size + lst.size());

    std::copy(lst.begin(), lst.end() , &(_vec.get()[_size]));
    _size+= lst.size();
}
template<typename T> void Vector<T>::push_back(uint n, T && value)
{
    if(_size+n > _capacity_size)
        expand_capacity(_size+n);

    for (int i = 0; i < n; i++)
        _vec[_size+i]= value;
    
    _size+= n;
}

template<typename T> void Vector<T>::drop_back(int n, bool rescale_capacity)
{
    if(n >= _size)
        _size=0;
    else
        _size-= n;

    if(rescale_capacity)
        expand_capacity(_size);
}

template<typename T> void Vector<T>::debug_print() const
{
    std::cout<<"\n"<<_capacity_size<<"\n"<<_size<<"\n";
    for (uint i = 0; i < _size; i++)
    {
        std::cout<<_vec[i];
        std::cout<<"    ";
    }
}

template<typename T> const uint Vector<T>::get_size() const
{
    return _size;
}

template<typename T> const uint Vector<T>::get_capacity_size() const
{
    return _capacity_size;
}

template<typename T> const uint Vector<T>::get_minimal_capacity_size() const
{
    return _minimal_capacity_size;
}
template<typename T> void Vector<T>::set_minimal_capacity_size(uint minimal_capacity_size)
{
    _minimal_capacity_size= minimal_capacity_size;
    expand_capacity(_size);
}

template<typename T> const CAPACITY_METHOD Vector<T>::get_capacity_method() const
{
    return _capacity_method;
}
template<typename T> void Vector<T>::set_capacity_method(CAPACITY_METHOD method)
{
    _capacity_method= method;
    expand_capacity(_size);
}

template<typename T> const double Vector<T>::get_multiplication_factor() const
{
    return _multiplication_factor;
}
template<typename T> void Vector<T>::set_multiplication_factor(double factor)
{
    _multiplication_factor= factor;
    expand_capacity(_size);
}

template<typename T> const uint Vector<T>::get_sum_factor() const
{
    return _sum_factor;
}
template<typename T> void Vector<T>::set_sum_factor(uint factor)
{
    _sum_factor= factor;
    expand_capacity(_size);
}

template<typename T> Vector<T>::~Vector()
{
    //Changed to smart pointers
    //if(_vec)
        //delete[] _vec;
}