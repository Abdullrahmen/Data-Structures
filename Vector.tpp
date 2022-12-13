template<typename T> Vector<T>::Vector():
_initial_capacity_size(DEFAULT_INITIAL_CAPACITY_SIZE),
_capacity_method(DEFAULT_CAPACITY_METHOD),
_multiplication_factor(DEFAULT_MULTIPLICATION_FACTOR),
_sum_factor(DEFAULT_SUM_FACTOR),
_capacity_size(0),
_size(0),
_vec(nullptr){}

template<typename T> Vector<T>::Vector(const Vector& vec):
_initial_capacity_size(vec._initial_capacity_size),
_capacity_method(vec._capacity_method),
_multiplication_factor(vec._multiplication_factor),
_sum_factor(vec._sum_factor),
_capacity_size(vec._capacity_size),
_size(vec._size),
_vec(new T[_capacity_size])
{
    //std::cout<<"\n"<<"copy constructor called"<<"\n";

    for (int i = 0; i < _size; i++)
        _vec[i] = vec._vec[i];
}

template<typename T> Vector<T>::Vector(Vector&& vec):
_initial_capacity_size(vec._initial_capacity_size),
_capacity_method(vec._capacity_method),
_multiplication_factor(vec._multiplication_factor),
_sum_factor(vec._sum_factor),
_capacity_size(vec._capacity_size),
_size(vec._size),
_vec(vec._vec)
{
    //std::cout<<"\n"<<"move constructor called"<<"\n";
    vec._capacity_size=0;
    vec._size=0;
    vec._vec= nullptr;
}

template<typename T> Vector<T>::Vector(std::initializer_list<T> ls):
_initial_capacity_size(DEFAULT_INITIAL_CAPACITY_SIZE),
_capacity_method(DEFAULT_CAPACITY_METHOD),
_multiplication_factor(DEFAULT_MULTIPLICATION_FACTOR),
_sum_factor(DEFAULT_SUM_FACTOR),
_capacity_size(0),
_size(0),
_vec(nullptr)
{
    //std::cout<<"\n"<<"initializer_list constructor called"<<"\n";
    expand_capacity(ls.size());

    std::copy(ls.begin(),ls.end(),_vec);
    /* or
    int i{0};
    for (auto &&j : ls)
    {
        _vec[i]= j;
        ++i;
    }   
    */
    _size= ls.size();
}

template<typename T> void Vector<T>::expand_capacity(int expand_to)
{
    if(expand_to== _capacity_size)
        return;

    int temp_capacity{_capacity_size};

    if (expand_to <= _initial_capacity_size)
        temp_capacity = _initial_capacity_size;    
    else
        switch (_capacity_method)
        {
        case MULTIPLICATION:
        {
            if(expand_to < temp_capacity)
            {
                while(true)
                {
                    if(int(temp_capacity/_multiplication_factor) > expand_to && int(temp_capacity/_multiplication_factor) > _initial_capacity_size)
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
            int f= floor(temp_capacity/double(_sum_factor)-expand_to/double(_sum_factor));
            auto t= temp_capacity-(_sum_factor * f);
            if(t <= _initial_capacity_size)
                temp_capacity= _initial_capacity_size;
            else
                temp_capacity= t;
        }break;
        default:
            throw std::invalid_argument("Unknown capacity method");
            break;
        }
    /* // The above SUM method is faster
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
    */

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

template<typename T> const int Vector<T>::get_size() const
{
    return _size;
}

template<typename T> const int Vector<T>::get_capacity_size() const
{
    return _capacity_size;
}

template<typename T> const int Vector<T>::get_initial_capacity_size() const
{
    return _initial_capacity_size;
}
template<typename T> void Vector<T>::set_initial_capacity_size(int initial_capacity_size)
{
    _initial_capacity_size= initial_capacity_size;
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

template<typename T> const int Vector<T>::get_sum_factor() const
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