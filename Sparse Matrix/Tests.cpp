#include "SM.h"
#include <assert.h>

/// @brief Constructors
void test1()
{
    SparseMat<int> mat{{5, 5}, 0};

    auto d{1};
    SparseMat<int>&& mat2{{3, 3}, d};

    SparseMat<int> mat3{mat2};

    SparseMat<int> mat4{std::move(mat2)};
}

/// @brief set_value 
void test2()
{
    SparseMat<int> mat{{5}, 0};
    mat.set_value({3}, 1);
    std::cout << mat[{2}];
    std::cout << mat[{3}];
    mat.set_value({3}, 2);
    std::cout << mat[{3}];
}