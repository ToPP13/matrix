#include <algorithm>
#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <gtest/gtest.h>
#include "../include/lib.h"
#include "../include/array.h"
#include "../include/matrix2d.h"

TEST(gtest_version, gtest_version_basic)
{
    ASSERT_GT(version(), 0);
}

TEST(gtest_Array, gtest_Array_basic)
{
    constexpr int DEF_VAL = -1;
    constexpr int NON_DEF_VAL = DEF_VAL+1;
    assert(DEF_VAL != NON_DEF_VAL);

    // assert size si zero on start
    Array<int, DEF_VAL> test_array;
    assert(test_array.size() == 0);

    // set non zero element
    test_array[1] = NON_DEF_VAL;
    assert(test_array.size() == 1);

    test_array[1] = DEF_VAL;
    assert(test_array.size() == 0);


    test_array[2] = NON_DEF_VAL;
    test_array[1] = NON_DEF_VAL;
    assert(test_array.size() == 2);
}

TEST(gtest_Matrix2D, gtest_Matrix2D_basic)
{
    Matrix2D<int, -1> matrix;
    assert(matrix.size() == 0); // все ячейки свободны
    auto a = matrix[0][0];
    assert(a == -1);
    assert(matrix.size() == 0);
    matrix[100][100] = 314;
    assert(matrix[100][100] == 314);
    assert(matrix.size() == 1);

    for(auto c: matrix)
    {
        int x;
        int y;
        int v;
        std::tie(x, y, v) = c;
        std::cout << x << y << v << std::endl;
    }
}


TEST(gtest_Matrix2D, gtest_Matrix2D_result)
{
    Matrix2D<int, 0> matrix;
    uint start = 0;
    uint end = 9;
    for (uint i = start; i<=end; i++)
    {
        matrix[i][i] = i;
        matrix[i][end-i] = end-i;
    }
    matrix.print(1,8);
    std::cout << matrix.size() << std::endl;


    matrix.print();
}


