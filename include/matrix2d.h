//
// Created by kirill on 16.11.2020.
//

#ifndef MATRIX_MATRIX2D_H
#define MATRIX_MATRIX2D_H

#include "array.h"

#include "algorithm"
#include <map>
#include <vector>
#include <iostream>
#include "string.h"
#include <iterator>


template<typename T, T default_value>
class Matrix2D
{
public:
    Matrix2D() {};

    Array<T, default_value> & operator[] (uint pos) {
        if (_data.find(pos) == _data.end())
        {
            Array<T, default_value> new_elem;
            _data[pos] = new_elem;
        }
        return _data[pos];
    };


    uint size()
    {
        uint total_size(0);
        for (auto & it : _data)
        {
            total_size += it.second.size();
        }
        return total_size;
    };
    void print(uint start, uint end)
    {
        for (uint i = start; i <= end; i++)
        {
            this->operator[](i).print(start, end);
        }
    }
    void print()
    {
        for (auto & array_pair : _data)
        {
            for (const auto & elem : array_pair.second.get_data())
            {
                std::cout << "[" << array_pair.first << "]";
                std::cout << "[" << elem.first << "]";
                std::cout << "=" << elem.second;
                std::cout <<  std::endl;
            }
        }
    }

    auto begin()
    {
        return matrix_iterator{*this, 0};
    }
    auto end()
    {
        return matrix_iterator{*this,  size()};
    }
private:
    class matrix_iterator {
    public:
        matrix_iterator(Matrix2D& o, uint it) :_o{o}, i{it}
        {
            // not fast at all
            for (auto array_pair : _o._data)
            {
                for (auto elem : array_pair.second.get_data())
                {
                    refs.push_back(std::make_tuple(array_pair.first, elem.first));
                }
            }
        };

        bool operator!=(const matrix_iterator& it) { return i != it.i; }

        void operator++()
        {
            ++i;
        }

        std::tuple<uint,uint,T> & operator*()
        {
            uint arr_ref, elem_ref;
            std::tie(arr_ref, elem_ref) = refs[i];
            T& val = _o[arr_ref][elem_ref];
            cur_val = std::tie(arr_ref, elem_ref, val);
            return cur_val;
        }

    private:
        Matrix2D& _o;
        uint i;
        std::tuple<uint,uint,T> cur_val;
        std::vector<std::tuple<uint,uint>> refs;
    };


private:
    std::map<uint, Array<T, default_value>> _data;
};


#endif //MATRIX_MATRIX2D_H
