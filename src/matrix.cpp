#ifndef __PRETTY_FUNCTION__
#include "pretty.h"
#include "../include/array.h"
#include "../include/matrix2d.h"
#endif


// Цепочка ответственности (Chain of responsibilily)

// позволяет передавать запросы последовательно по цепочке обработчиков.
// Каждый последующий обработчик решает,
// может ли он обработать запрос сам и стоит ли передавать запрос дальше по цепи.

// interrupt handler, tsr
// обработчики ошибки
// почтовые фильтры


int main(int, char *[]) {

    Matrix2D<int, -1> matrix;
    matrix[100][100] = 314;
    for(auto c: matrix)
    {
        int x;
        int y;
        int v;
        std::tie(x, y, v) = c;
        std::cout << x << y << v << std::endl;
    }


    Matrix2D<int, 0> matrix2;
    uint start = 0;
    uint end = 9;
    for (uint i = start; i<=end; i++)
    {
        matrix2[i][i] = i;
        matrix2[i][end-i] = end-i;
    }
    matrix2.print(1,8);
    std::cout << matrix2.size() << std::endl;
    matrix2.print();

    return 0;
}