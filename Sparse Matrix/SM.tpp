/// Start Coord class

Coord::Coord() : _coord()
{
    _coord.set_sum_factor(1);
    _coord.set_capacity_method(SUM);
    _coord.set_minimal_capacity_size(1);
}

Coord::Coord(const Vector<int> &coord) : _coord(coord)
{
    _coord.set_sum_factor(1);
    _coord.set_capacity_method(SUM);
    _coord.set_minimal_capacity_size(1);
}

Coord::Coord(Vector<int> &&coord) : _coord(std::move(coord))
{
    _coord.set_sum_factor(1);
    _coord.set_capacity_method(SUM);
    _coord.set_minimal_capacity_size(1);
}

Vector<int> &Coord::get_coord()
{ return _coord; }

int Coord::get_n_dimensions() const
{ return _coord.get_size(); }

/// Finish Coord class
/// Start Item class

template <class T>
Item<T>::Item() : _item(nullptr),
                  _idx(){}

template <class T>
Item<T>::Item(const Item& item) :
_item(std::make_unique<T>(*(item._item))),
_idx(item._idx) {}

template <class T>
Item<T>::Item(uint idx, const T &default_value) : _item(std::make_unique<T>(default_value)),
                                                  _idx(idx) {}

template <class T>
Item<T>::Item(uint idx, T &&default_value) : _item(std::make_unique<T>(std::move(default_value))),
                                             _idx(idx) {}

template <class T>
const std::unique_ptr<T> &Item<T>::get_item()
{ return _item; }

template <class T>
const uint& Item<T>::get_idx()
{ return _idx; }

template <class T>
void Item<T>::set_item(std::unique_ptr<T> &&item)
{ _item= std::move(item); }

template <class T>
void Item<T>::set_idx(const uint &idx)
{ _idx= idx; }

/// Finish Item class
/// Start SparseMat class

/*
template <class T>
SparseMat<T>::SparseMat() : _special_values{nullptr},
                            _default_value{nullptr},
                            _shape{} {}*/

template <class T>
SparseMat<T>::SparseMat(const SparseMat<T> &mat) : 
_special_values{nullptr},
_default_value{std::make_unique<T>(*(mat._default_value.get()))},
_shape{mat._shape} 
{
    if(mat._special_values)
        _special_values= std::make_unique<SPECIAL_VALUES_TYPE>(*(mat._special_values.get()));

    std::cout<<"Copy constructor called.\n";
}

template <class T>
SparseMat<T>::SparseMat(SparseMat<T> &&mat) : _special_values{std::move(mat._special_values)},
                                              _default_value{std::move(mat._default_value)},
                                              _shape{mat._shape} {std::cout<<"Move constructor called.\n";}

template <class T>
SparseMat<T>::SparseMat(const Coord &shape, const T &default_value) : 
_special_values{nullptr},
_default_value{std::make_unique<T>(default_value)},
_shape{shape} 
{
    std::cout << "Copy default_value constructor called.\n";
    specify_special_values_type();
}

template <class T>
SparseMat<T>::SparseMat(const Coord &shape, T &&default_value) : 
_special_values{nullptr},
_default_value{std::make_unique<T>(std::move(default_value))},
_shape{shape} 
{
    std::cout << "Move default_value constructor called.\n";
    specify_special_values_type();
}

template <class T>
void SparseMat<T>::set_value(const Coord &coord, const T &value)
{
    if(coord.get_n_dimensions() != _shape.get_n_dimensions())
        throw std::invalid_argument("invalid coordinates");

    auto tmp_special_values{_special_values.get()};
    for (int i = 0; i < _shape.get_n_dimensions()-1; i++)
        auto tmp_special_values= &(*tmp_special_values)[coord.get_coord()[i]];

    tmp_special_values->push_back(Item{coord.get_coord()[-1], value});    
}

template <class T>
void SparseMat<T>::set_value(const Coord &coord, T &&value)
{
    if (coord.get_n_dimensions() != _shape.get_n_dimensions())
        throw std::invalid_argument("invalid coordinates");

    auto tmp_special_values{_special_values.get()};
    for (int i = 0; i < _shape.get_n_dimensions() - 1; i++)
        auto tmp_special_values = &((*tmp_special_values)[coord.get_coord()[i]]); //loop till last dimension
    
    tmp_special_values->push_back(Item{coord.get_coord()[-1], std::move(value)});
}

template <class T>
T &SparseMat<T>::operator[](const _SparseMat::Coord &coord)
{
    auto tmp_special_values{_special_values.get()};
    for (int i = 0; i < _shape.get_n_dimensions() - 1; i++)
        auto tmp_special_values = &((*tmp_special_values)[coord.get_coord()[i]]); // loop till last dimension

    for (auto &&i : *tmp_special_values)
    {
        
    }
}


template <class T>
void SparseMat<T>::specify_special_values_type()
{
    switch (_shape.get_n_dimensions())
    {
    case 0:
        _special_values= nullptr;
        break;

    case 1:
        _special_values= std::make_unique<SPECIAL_VALUES_TYPE>(LL<Item<T>>{});
        break;

    case 2:
        _special_values= std::make_unique<SPECIAL_VALUES_TYPE>(LL<LL<Item<T>>>{});
        break;

    case 3:
        _special_values= std::make_unique<SPECIAL_VALUES_TYPE>(LL<LL<LL<Item<T>>>>{});
        break;

    case 4:
        _special_values= std::make_unique<SPECIAL_VALUES_TYPE>(LL<LL<LL<LL<Item<T>>>>>{});
        break;

    case 5:
        _special_values= std::make_unique<SPECIAL_VALUES_TYPE>(LL<LL<LL<LL<LL<Item<T>>>>>>{});
        break;

    default:
        throw std::invalid_argument("Shape dimensions > 5");
    }
}
