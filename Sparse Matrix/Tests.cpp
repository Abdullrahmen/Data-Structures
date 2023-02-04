#include "SM.h"
#include <assert.h>

/// @brief Constructors
void test1()
{
    SparseMat<int> mat{{5, 5}, 0};

    auto d{1};
    SparseMat<int> &&mat2{{3, 3}, d};

    SparseMat<int> mat3{mat2};

    SparseMat<int> mat4{std::move(mat2)};

    try
    {
        SparseMat<int> mat{{0, 5, 3}, 0};
    }
    catch(const std::exception& e)
    {
        assert(std::string(e.what()) == "invalid shape");
    }

    try
    {
        SparseMat<int> mat{{1, 5, 3, 5, 6, 4}, 0};
    }
    catch (const std::exception &e)
    {
        assert(std::string(e.what()) == "Shape dimensions > 5");
    }
    std::cout<<"Test1 passed"<<"\n";
}

/// @brief Test multidimensional constructors
void test2()
{
    auto d{1};
    SparseMat<int> mat{{5}, d};
    SparseMat<int> mat2{{5, 3}, -1};
    SparseMat<int> mat3{{5, 3, 2}, d};
    SparseMat<int> mat4{{5, 1, 4, 3}, 3};
    SparseMat<int> mat5{{5, 1, 4, 3, 2}, d};
    std::cout<<"Test2 passed"<<"\n";
}

/// @brief set_value, get_value, reset_value
void test3()
{
    SparseMat<int> mat{{5, 3}, -1};

    try
    {
        mat.set_value({3}, 1);
    }
    catch(const std::exception& e)
    {
        assert(std::string(e.what()) == "invalid coordinates");
    }

    mat.set_value({3, 2}, 6);
    assert((mat[{3, 2}] == 6));

    mat.set_value({3, 2}, 5);
    assert((mat[{3, 2}] == 5));

    mat.reset_value({3, 2});
    assert((mat[{3, 2}] == -1));

    assert((mat[{1, 1}] == -1));
    assert((mat[{2, 1}] == -1));
    assert((mat[{2, 2}] == -1));
    assert((mat[{4, 2}] == -1));

    mat.set_value({4, 2}, 42);
    assert((mat[{4, 2}] == 42));

    try
    {
        std::cout << mat[{2, 3}];//shape is (5,3)
    }
    catch (const std::exception &e)
    {
        assert(std::string(e.what()) == "invalid coordinates");
    }
    std::cout<<"Test3 passed"<<"\n";
}

/// @brief Test debug_print
void test4()
{
    std::cout << "1D Matrix";

    SparseMat<int> mat{{5}, 0};
    mat.set_value({2},3);
    mat.debug_print();

    std::cout << "\n"
              << "2D Matrix\n";

    SparseMat<int> mat2{{5,3}, 0};
    mat2.set_value({0, 0}, 1);
    mat2.set_value({-1, -1}, -1);
    mat2.debug_print();

    std::cout << "\n"
              << "\n"
              << "3D Matrix\n";

    SparseMat<int> mat3{{3, 3, 2}, 0};
    mat3.set_value({0, 0, 0}, 1);
    mat3.set_value({0, -1, -1}, -1);
    mat3.debug_print();

    std::cout << "\n"
              << "\n"
              << "4D Matrix\n";

    SparseMat<int> mat4{{2, 2, 2, 2}, 0};
    mat4.set_value({0, 0, 0, 1}, 1);
    mat4.set_value({-1, -1, 0, 0}, -1);
    mat4.debug_print();

    std::cout << "\n"
              << "\n"
              << "5D Matrix\n";

    SparseMat<int> mat5{{2, 2, 2, 2, 2}, 0};
    mat5.set_value({0, 0, 0, 1, 0}, 1);
    mat5.set_value({-1, -1, 0, 0, 1}, -1);
    mat5.debug_print();
    std::cout<<"Test4 passed"<<"\n";
}