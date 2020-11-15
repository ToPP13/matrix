//
// Created by kirill on 16.11.2020.
//

#ifndef MATRIX_ARRAY_H
#define MATRIX_ARRAY_H

#include "algorithm"
#include <map>
#include <vector>
#include <iostream>
#include <iterator>


template<typename T, T default_value>
class Array
{
public:
    Array(){};
    T& operator[] (uint pos) {
        shrink_last_element();
        if (_values.find(pos) == _values.end())
        {
            _values.insert(std::pair<uint,T>(pos,default_value));
        }
        _last_pos = pos;
        return _values[pos];
    };
    void shrink_last_element()
    {
        if (_values.find(_last_pos) != _values.end())
        {
            if (_values[_last_pos] == default_value)
                _values.erase(_last_pos);
        }
    }
    void print(uint start, uint end)
    {
        shrink_last_element();
        for (uint i = start; i < end; i++)
        {
            std::cout << this->operator[](i);
            std::cout << " ";
        }
        std::cout << this->operator[](end);
        std::cout << std::endl;
    }

    void print()
    {
        shrink_last_element();
        for (auto & i : _values)
        {
            std::cout << i.first << " " << i.second << std:: endl;
        }
    }
    uint size()
    {
        shrink_last_element();
        return _values.size();
    };
    const std::map<uint, T> & get_data(){return _values;};

    auto begin()
    {
        return array_iterator{*this, 0};
    }
    auto end()
    {
        return array_iterator{*this, size()};
    }
private:

    class array_iterator {
    public:
        array_iterator(Array& o, uint it) :_o{o}, i{it}
        {
            // not fast at all
            for (auto elem : o.get_data())
            {
                vals.push_back(std::tuple<uint, T>{elem.first, elem.second});
            }
        };

        bool operator!=(const array_iterator& it) { return i != it.i; }

        void operator++() {++i;}

        std::tuple<uint,T> & operator*()
        {
            return vals[i];
        }

    private:
        Array& _o;
        std::vector<std::tuple<uint,T>> vals;
        uint i;
    };

    uint _last_pos;
    std::map<uint, T> _values;

};

#endif //MATRIX_ARRAY_H
