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
LL<Item<T>>* SparseMat<T>::get_last_dim(const Coord& coord)
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
    
        //std::cout<<std::to_string(crd[0]);
        //auto l{std::get<1>(*_special_values)};
        //auto itm_l {l[crd[0]]};
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
        if ((*itm_lst)[i].get_idx() == coord.get_coord()[-1])
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
        if ((*itm_lst)[i].get_idx() == coord.get_coord()[-1])
        {
            (*itm_lst)[i].set_item(std::make_unique<T>(std::move(value)));
            break;
        }

    itm_lst->push_back(Item{coord.get_coord()[-1], std::move(value)});
}

template <class T>
void SparseMat<T>::reset_value(Coord coord)
{
    if (!check_coord_validity(coord))
        throw std::invalid_argument("invalid coordinates");

    if (_shape.get_n_dimensions() == 0)
        throw std::invalid_argument("Empty matrix");

    LL<Item<T>> *itm_lst{get_last_dim(coord)};

    for (int i = 0; i < itm_lst->get_size(); i++)
        if ((*itm_lst)[i].get_idx() == coord.get_coord()[-1])
        {
            ///@todo
            ///Until add drop(delete with index) method in Vector class 
            (*itm_lst)[i].set_item(std::make_unique<T>(*(_default_value.get())));
            return;
        }
}

template <class T>
T &SparseMat<T>::get_item(Coord &coord)
{
    if (!check_coord_validity(coord))
        throw std::invalid_argument("invalid coordinates");

    if (_shape.get_n_dimensions() == 0)
        throw std::invalid_argument("Empty matrix");

    LL<Item<T>> *itm_lst{get_last_dim(coord)};

    for (int i = 0; i < itm_lst->get_size(); i++)
        if ((*itm_lst)[i].get_idx() == coord.get_coord()[-1])
            return *((*itm_lst)[i].get_item());

    return *_default_value;
}

template <class T>
const T &SparseMat<T>::operator[](Coord coord)
{
    return get_item(coord);
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
        for (int i = 0; i < _shape.get_coord()[0]; i++)
            std::get<1>(*_special_values).push_back(LL<Item<T>>{});
        break;

    case 3:
        _special_values= std::make_unique<SPECIAL_VALUES_TYPE>(LL<LL<LL<Item<T>>>>{});
        for (int i = 0; i < _shape.get_coord()[0]; i++)
        {
            std::get<2>(*_special_values).push_back(LL<LL<Item<T>>>{});
            for (int j = 0; j < _shape.get_coord()[1]; j++)
                std::get<2>(*_special_values)[i].push_back(LL<Item<T>>{});
        }    
        break;

    case 4:
        _special_values= std::make_unique<SPECIAL_VALUES_TYPE>(LL<LL<LL<LL<Item<T>>>>>{});
        for (int i = 0; i < _shape.get_coord()[0]; i++)
        {
            std::get<3>(*_special_values).push_back(LL<LL<LL<Item<T>>>>{});
            for (int j = 0; j < _shape.get_coord()[1]; j++)
            {
                std::get<3>(*_special_values)[i].push_back(LL<LL<Item<T>>>{});
                for (int k = 0; k < _shape.get_coord()[2]; k++)
                    std::get<3>(*_special_values)[i][j].push_back(LL<Item<T>>{});
            }
        }
        break;

    case 5:
    {
        _special_values= std::make_unique<SPECIAL_VALUES_TYPE>(LL<LL<LL<LL<LL<Item<T>>>>>>{});
        auto &sp_values { std::get<4>(*_special_values) };
        for (int i = 0; i < _shape.get_coord()[0]; i++)
        {
            sp_values.push_back(LL<LL<LL<LL<Item<T>>>>>{});
            for (int j = 0; j < _shape.get_coord()[1]; j++)
            {
                sp_values[i].push_back(LL<LL<LL<Item<T>>>>{});
                for (int k = 0; k < _shape.get_coord()[2]; k++)
                {
                    sp_values[i][j].push_back(LL<LL<Item<T>>>{});
                    for (int z = 0; z < _shape.get_coord()[3]; z++)
                        sp_values[i][j][k].push_back(LL<Item<T>>{});
                }
            }
        }
        break;
    }
    default:
        throw std::invalid_argument("Shape dimensions > 5");
    }
}

template <class T>
void SparseMat<T>::debug_print() 
{
    if(!_shape.get_n_dimensions())
        return;

    std::string print_mat{""};
    std::string dim_start_delim{"{"};
    std::string dim_end_delim{"}"};
    std::string itm_delim{" "};

    int n_loops{_shape.get_n_dimensions()}; // number of nested for loops

    int loops_idx[n_loops]; // like i,j,k but in an array
    for (int i = 0; i < n_loops; i++)
        loops_idx[i] = 0;

    int max_idx[n_loops]; // like in for(; i < counter ;), but the counters in an array
    for (int i = 0; i < n_loops; i++)
        max_idx[i]= _shape.get_coord()[i];
    

    bool is_finished = false;

    for (int i = 1; i < n_loops; i++)
        print_mat.append(dim_start_delim);
    print_mat.append("\n");
    //print_mat.append(dim_start_delim);
    while (!is_finished)
    {
        for (; loops_idx[0] < max_idx[0]; loops_idx[0]++)
        {
            Coord crd;
            for (int i = 0; i < n_loops; i++)
                crd.get_coord().push_back(loops_idx[i]);
            
            print_mat.append(std::to_string(get_item(crd)));
            print_mat.append(itm_delim);
        }
        print_mat.pop_back();
        print_mat.append("\n");
        // print_mat.append(dim_end_delim);
        --loops_idx[0]; // to cancel last increment
        // Here it will increment the last loop_idx which isn't equal to max_idx[i]-1
        // eg. after first above for loop loops_idx will be (max-1, 0, 0)
        // So it will be after this loop (0, 1, 0) and start from the beginning...
        for (int i = 0; i < n_loops + 1; i++) //+1 to know if all loops are finished
        {
            if (i == n_loops)
            {is_finished = true; break;}

            if (loops_idx[i] == max_idx[i] - 1)
                continue;

            for (int j = 1; j < i; j++)
                print_mat.append(dim_end_delim);
            // print_mat.pop_back();
            for (int j = 1; j < i; j++)
                print_mat.append(dim_start_delim);
            if (i>1)
                print_mat.append("\n");
            
            //print_mat.append(dim_start_delim);
            ++loops_idx[i];
            for (int j = 0; j < i; j++) // make any previous loop = 0
                loops_idx[j] = 0;

            break;
        }
    }
    //print_mat.pop_back();
    for (int i = 1; i < n_loops; i++)
        print_mat.append(dim_end_delim);

    std::cout<<print_mat;
}
