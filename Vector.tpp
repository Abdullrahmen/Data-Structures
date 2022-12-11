template<typename T> Vector<T>::Vector():
_initial_capacity_size(DEFAULT_INITIAL_CAPACITY_SIZE),
_capacity_method(DEFAULT_CAPACITY_METHOD),
_multiplication_factor(DEFAULT_MULTIPLICATION_FACTOR),
_sum_factor(DEFAULT_SUM_FACTOR),
_capacity_size(0),
_size(0),
_vec(nullptr){}

template<typename T> template<typename ... E> Vector<T>::Vector(E&& ... vec):
_initial_capacity_size(DEFAULT_INITIAL_CAPACITY_SIZE),
_capacity_method(DEFAULT_CAPACITY_METHOD),
_multiplication_factor(DEFAULT_MULTIPLICATION_FACTOR),
_sum_factor(DEFAULT_SUM_FACTOR),
_capacity_size(0),
_size(0),
_vec(nullptr)
{
    expand_capacity(sizeof...(vec));

    int i{0};

    ([&]{
        _vec[i] = static_cast<T>(std::move(vec));
        ++i;
    }(),...);

    _size= i;
}

template<typename T> void Vector<T>::expand_capacity(int expand_to)
{
    if(expand_to== _capacity_size)
        return;

    int temp_capacity{_capacity_size};

    if (expand_to <= _initial_capacity_size)
        temp_capacity = _initial_capacity_size;

    else if(expand_to < temp_capacity)
        switch (_capacity_method)
        {
        case MULTIPLICATION:
            while(true)
            {
                if(int(temp_capacity/_multiplication_factor) > expand_to && int(temp_capacity/_multiplication_factor) > _initial_capacity_size)
                    temp_capacity /= _multiplication_factor;
                else
                    break;
            }
            break;
        case SUM:
            while(true)
            {
                if(temp_capacity-_sum_factor > expand_to && temp_capacity-_sum_factor > _initial_capacity_size)
                    temp_capacity -= _sum_factor;
                else
                    break;
            }
            break;
        default:
            throw std::invalid_argument("Unknown capacity method");
            break;
        }

    else
    {
        switch (_capacity_method)
        {
        case MULTIPLICATION:
            while(temp_capacity < expand_to)
                temp_capacity *= _multiplication_factor;
            break;
        case SUM:
            while(temp_capacity < expand_to)
                temp_capacity += _sum_factor;
            break;
        default:
            throw std::invalid_argument("Unknown capacity method");
            break;
        }
    }

    if(_capacity_size==temp_capacity) //the capacity is good
        return;
    _capacity_size= temp_capacity;

    T* temp_vec= new T[_capacity_size];
    for (int i = 0; i < _size; i++)
        temp_vec[i]= _vec[i];

    std::swap(temp_vec, _vec);
    if(temp_vec)
        delete[] temp_vec;
}

template<typename T> void Vector<T>::push_back(T && value)
{
    if(_size+1 > _capacity_size)
        expand_capacity(_size+1);
    
    ++_size;
    _vec[_size-1]= value;
}

template<typename T> void Vector<T>::print() const
{
    std::cout<<"\n"<<_capacity_size<<"\n"<<_size<<"\n";
    for (int i = 0; i < _size; i++)
    {
        std::cout<<_vec[i];
        std::cout<<"    ";
    }
}

template<typename T> int Vector<T>::get_size() const
{
    return _size;
}

template<typename T> int Vector<T>::get_capacity_size() const
{
    return _capacity_size;
}

template<typename T> int Vector<T>::get_initial_capacity_size() const
{
    return _initial_capacity_size;
}
template<typename T> void Vector<T>::set_initial_capacity_size(int initial_capacity_size)
{
    _initial_capacity_size= initial_capacity_size;
    expand_capacity(_size);
}

template<typename T> CAPACITY_METHOD Vector<T>::get_capacity_method() const
{
    return _capacity_method;
}
template<typename T> void Vector<T>::set_capacity_method(CAPACITY_METHOD method)
{
    _capacity_method= method;
    expand_capacity(_size);
}

template<typename T> int Vector<T>::get_multiplication_factor() const
{
    return _multiplication_factor;
}
template<typename T> void Vector<T>::set_multiplication_factor(int factor)
{
    _multiplication_factor= factor;
    expand_capacity(_size);
}

template<typename T> int Vector<T>::get_sum_factor() const
{
    return _sum_factor;
}
template<typename T> void Vector<T>::set_sum_factor(int factor)
{
    _sum_factor= factor;
    expand_capacity(_size);
}

template<typename T> Vector<T>::~Vector()
{
    if(_vec)
        delete[] _vec;
}