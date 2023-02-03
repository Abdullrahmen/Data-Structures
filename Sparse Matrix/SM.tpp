/// Start Coord class

Coord::Coord() : _coord()
{
    _coord.set_sum_factor(1);
    _coord.set_capacity_method(SUM);
    _coord.set_minimal_capacity_size(1);
}

Coord::Coord(std::initializer_list<int> &&coord) : _coord(std::move(coord))
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

const Vector<int> &Coord::get_coord() const
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

    //std::cout<<"Copy constructor called.\n";
}

template <class T>
SparseMat<T>::SparseMat(SparseMat<T> &&mat) : _special_values{std::move(mat._special_values)},
                                              _default_value{std::move(mat._default_value)},
                                              _shape{mat._shape} 
                                                {
                                                //std::cout<<"Move constructor called.\n";
                                                }

template <class T>
SparseMat<T>::SparseMat(const Coord &shape, const T &default_value) : 
_special_values{nullptr},
_default_value{std::make_unique<T>(default_value)},
_shape{shape} 
{
    //std::cout << "Copy default_value constructor called.\n";
    if(!check_shape_validity())
        throw std::invalid_argument("invalid shape");
    specify_special_values_type();
}

template <class T>
SparseMat<T>::SparseMat(const Coord &shape, T &&default_value) : 
_special_values{nullptr},
_default_value{std::make_unique<T>(std::move(default_value))},
_shape{shape} 
{
    //std::cout << "Move default_value constructor called.\n";
    if (!check_shape_validity())
        throw std::invalid_argument("invalid shape");
    specify_special_values_type();
}

template <class T>
bool SparseMat<T>::check_shape_validity()
{
    for (int i = 0; i < _shape.get_n_dimensions(); i++)
    {
        if(_shape.get_coord()[i]<=0)
            return false;
    }
    return true;
}

template <class T>
bool SparseMat<T>::check_coord_validity(Coord &coord)
{
    if (coord.get_n_dimensions() != _shape.get_n_dimensions())
        return false;

    for (int i = 0; i < _shape.get_n_dimensions(); i++)
    {
        if (coord.get_coord()[i] < 0)
            coord.get_coord()[i] += _shape.get_coord()[i]; // flip the direction

        if (coord.get_coord()[i] < 0 || coord.get_coord()[i] >= _shape.get_coord()[i])
            return false;
    }
    return true;
}

template <class T>
LL<Item<T>>* SparseMat<T>::get_last_dim(const Coord &coord)
{
    // Another solution is visitor pattern

    LL<Item<T>> *itm_lst{nullptr};
    auto &crd{coord.get_coord()};
    switch (_shape.get_n_dimensions())
    {
    case 1:
        itm_lst = &std::get<0>(*_special_values);
        break;

    case 2:
        itm_lst = &std::get<1>(*_special_values)[crd[0]];
        break;

    case 3:
        itm_lst = &std::get<2>(*_special_values)[crd[0]][crd[1]];
        break;

    case 4:
        itm_lst = &std::get<3>(*_special_values)[crd[0]][crd[1]][crd[2]];
        break;

    case 5:
        itm_lst = &std::get<4>(*_special_values)[crd[0]][crd[1]][crd[2]][crd[3]];
        break;

    default:
        throw std::invalid_argument("Shape dimension exceed");
    }
    return itm_lst;
}

template <class T>
void SparseMat<T>::set_value(Coord coord, const T &value)
{
    if (!check_coord_validity(coord))
        throw std::invalid_argument("invalid coordinates");

    if (_shape.get_n_dimensions() == 0)
        return;

    LL<Item<T>> *itm_lst{get_last_dim(coord)};

    for (int i = 0; i < itm_lst->get_size(); i++)
        if ((*itm_lst)[i].get_idx() == coord.get_coord()[0])
        {
            (*itm_lst)[i].set_item(std::make_unique<T>(value));
            break;
        }

    itm_lst->push_back(Item{coord.get_coord()[-1], value});
}

template <class T>
void SparseMat<T>::set_value(Coord coord, T &&value)
{
    if (!check_coord_validity(coord))
        throw std::invalid_argument("invalid coordinates");

    if (_shape.get_n_dimensions() == 0)
        return;

    LL<Item<T>> *itm_lst{get_last_dim(coord)};

    for (int i = 0; i < itm_lst->get_size(); i++)
        if ((*itm_lst)[i].get_idx() == coord.get_coord()[0])
        {
            (*itm_lst)[i].set_item(std::make_unique<T>(std::move(value)));
            break;
        }

    itm_lst->push_back(Item{coord.get_coord()[-1], std::move(value)});
}

template <class T>
const T &SparseMat<T>::operator[](Coord coord)
{
    if (!check_coord_validity(coord))
        throw std::invalid_argument("invalid coordinates");

    if (_shape.get_n_dimensions() == 0)
        throw std::invalid_argument("Empty matrix");

    LL<Item<T>> *itm_lst{get_last_dim(coord)};

    for (int i = 0; i < itm_lst->get_size(); i++)
        if ((*itm_lst)[i].get_idx() == coord.get_coord()[0])
            return *((*itm_lst)[i].get_item());

    return *_default_value;
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
