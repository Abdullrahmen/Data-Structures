#include "SM.h"
#include <assert.h>

/// @brief Constructors
void test1()
{
    SparseMat<int> mat{Coord{Vector<int>{5, 5}}, 0};

    auto d{1};
    SparseMat<int>&& mat2{Coord{Vector<int>{3, 3}}, d};

    SparseMat<int> mat3{mat2};

    SparseMat<int> mat4{std::move(mat2)};
}

/// @brief set_value 
void test2()
{

}