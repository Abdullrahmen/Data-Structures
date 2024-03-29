// Uses Linked List to create general(multitype) multidimensional Sparse Matrix.
#ifndef SM_H_
#define SM_H_
#include "../Linked List/Singly LL.h"
#include "../Vector/Vector.h"
#include <memory>
#include <initializer_list>
#include <iostream>
#include <variant>

using uint = unsigned long;

/// Default Linked List
#define LL SinglyLinkedList

namespace _SparseMat
{

    /// @brief Shape or coordinates
    /// @todo more in Coord like 0 auto deletion etc...
    class Coord
    {
    private:
        Vector<int> _coord;

    public:
        Coord();
        Coord(std::initializer_list<int> &&coord);
        Coord(const Vector<int> &coord);
        Coord(Vector<int> &&coord);

        Vector<int> &get_coord();
        const Vector<int> &get_coord() const;
        int get_n_dimensions() const;
    };

    /// @brief Contains the item and its real last coordinate (idx)
    template <typename T>
    struct Item
    {
    private:
        std::unique_ptr<T> _item;

        /// @brief Real last-dimension index/coordinate of this item
        uint _idx;

    public:
        Item();
        Item(const Item& item);
        Item(uint idx, const T &default_value);
        Item(uint idx, T &&default_value);

        const std::unique_ptr<T> &get_item();

        /// @brief Get real last-dimension index/coordinate of this item
        /// @return Real index
        const uint &get_idx();

        void set_item(std::unique_ptr<T> &&item);

        /// @brief Set real last-dimension index/coordinate of this item
        void set_idx(const uint& idx);
    };
}// namespace _SparseMat
using namespace _SparseMat;

/// @brief General (multitype) sparse matrix -> can overload to make numbers matrix
/// @tparam T Matrix items' type -> eg. int
/// @note The matrix is zero based index
template <typename T>
class SparseMat
{
private:
    /// @brief The shape of the matrix
    Coord _shape;

    /// @brief The matrix is filled with this value
    /// except special values stored with their indexes(coordinates) in _special_values
    std::unique_ptr<T> _default_value;

    /* Up to 5D Sparse Matrix
    1D -> LL<Item<T>>*,
    2D -> LL<LL<Item<T>>>*,
    3D -> LL<LL<LL<Item<T>>>>*,
    4D -> LL<LL<LL<LL<Item<T>>>>>*,
    5D -> LL<LL<LL<LL<LL<Item<T>>>>>>*
    Another solution: use a pointer to void then cast it in the constructor after the dimension specified
    */
    ///@todo
    ///@todo Another solution: add LL member in Item class -> better (future version)
    ///@todo
    #define SPECIAL_VALUES_TYPE std::variant<LL<Item<T>>,\
                                             LL<LL<Item<T>>>,\
                                             LL<LL<LL<Item<T>>>>,\
                                             LL<LL<LL<LL<Item<T>>>>>,\
                                             LL<LL<LL<LL<LL<Item<T>>>>>>>
    /// @brief All values except _default_value in the matrix
    std::unique_ptr<SPECIAL_VALUES_TYPE> _special_values;

    /// @brief Check _shape validity
    /// @return _shape validity
    bool check_shape_validity();
    
    /// @brief Check coordinate validity and if there are negative flip the direction
    /// @param coord 
    /// @return coordinate validity
    bool check_coord_validity(Coord &coord);

    /// @brief Specify _special_values type according to the dimension of the shape
    void specify_special_values_type();

    /// @brief Get last dimension from special_values according to coordinate and shape dimension
    /// @param coord full coordinate
    /// @return Last dimension from special_values
    /// @note coord won't checked (assume already checked + shape dimension>0)
    /// @note O(1)
    LL<Item<T>> *get_last_dim(const Coord &coord);

    /// @brief Get item from the matrix
    /// @param coord
    /// @return The item that has the coord
    /// @note O(n) where n is the number of the special values in this dimension
    [[nodiscard]] T &get_item(Coord &coord);

public:
    /// @brief Empty constructor
    ///SparseMat();

    /// @brief Copy constructor
    SparseMat(const SparseMat<T> &mat);

    /// @brief Move constructor
    SparseMat(SparseMat<T> &&mat);

    /// @brief Constructor
    /// @param shape The shape of the matrix up to 5D
    /// @param default_value Default (Filled) value
    SparseMat(const Coord &shape, const T &default_value);
    SparseMat(const Coord &shape, T &&default_value);

    // Deprecated -> changed to reset_value method
    /*@note If value is a nullptr then the value in the coordinate will reset to the default value*/
    /// @brief Set a value to a specific coordinates.
    /// @param coord
    /// @param value
    /// @note O(1)
    void set_value(Coord coord, const T &value);
    void set_value(Coord coord, T &&value);

    /// @brief Get item from the matrix
    /// @param coord
    /// @return The item that has the coord
    /// @note O(n) where n is the number of the special values in this dimension
    const T &operator[](Coord coord);

    /// @todo
    /// @brief
    /// @param idx
    /// @return A new sparse matrix with less one dimension or if dimension is 1 return the item that has the idx
    //std::variant<SparseMat<T>,T&> operator[](uint idx);

    /// @brief Reset the value in the coordinate to the default value (if the value isn't already default value)
    /// @param coord
    /// @note O(n) where n is the number of the special values in this dimension
    void reset_value(Coord coord);

    /// @todo efficient print method
    /// @brief inefficient print method just for debugging
    /// @note O(n) where n is the number of the values in the matrix
    void debug_print();

    //~SparseMat();
};
#include "SM.tpp"
#endif // SM_H_
