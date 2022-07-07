//
// Created by adeon on 7/6/22.
//
// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#ifndef TEMPLATE_ITERATORS_HPP
#define TEMPLATE_ITERATORS_HPP

#include <iostream>

/*
 * Rnd access iterators.
 * BIG BIG TODO
 */

namespace bsd {
    template<typename C>
    class rnd_iterator {
        C* ptr;
    public:
        using iterator_category = std::random_access_iterator_tag;
        using value_type = C;
        using reference = C&;
        using pointer = C*;
        using difference_type = long;

        explicit rnd_iterator(C* p): ptr{p} {};

        reference operator*() const { return *ptr; }
        pointer operator->() const { return ptr; }

        rnd_iterator& operator++() { ptr++; return *this; }
        rnd_iterator& operator--() { ptr--; return *this; }
        rnd_iterator operator++(int) { ptr++; return *this; }
        rnd_iterator operator--(int) { ptr--; return *this; }
        difference_type operator-(const rnd_iterator& it) const { return ptr - it.ptr; }
        rnd_iterator operator+(const difference_type& diff) const { return rnd_iterator(ptr + diff); }
        rnd_iterator operator-(const difference_type& diff) const { return rnd_iterator(ptr - diff); }
        reference operator[](const difference_type& offset) const { return *(*this + offset); }

        bool operator==(const rnd_iterator& it) const { return ptr == it.ptr; }
        bool operator!=(const rnd_iterator& it) const { return ptr != it.ptr; }
        bool operator<(const rnd_iterator& it) const { return ptr < it.ptr; }
        bool operator>(const rnd_iterator& it) const { return ptr > it.ptr; }
        bool operator>=(const rnd_iterator& it) const { return ptr >= it.ptr; }
        bool operator<=(const rnd_iterator& it) const { return ptr <= it.ptr; }
    };

    template<typename C>
    class reverse_rnd_iterator {
        C* ptr;
    public:
        using iterator_category = std::random_access_iterator_tag;
        using value_type = C;
        using reference = C&;
        using pointer = C*;
        using difference_type = long;

        explicit reverse_rnd_iterator(C* p): ptr{p} {};

        reference operator*() const { return *ptr; }
        pointer operator->() const { return ptr; }

        reverse_rnd_iterator& operator++() { --ptr; return *this; }
        reverse_rnd_iterator& operator--() { ++ptr; return *this; }
        reverse_rnd_iterator operator++(int) { --ptr; return *this; }
        reverse_rnd_iterator operator--(int) { ++ptr; return *this; }
        difference_type operator-(const reverse_rnd_iterator& it) const { return it.ptr - ptr; }
        reverse_rnd_iterator operator+(const difference_type& diff) const { return reverse_rnd_iterator(ptr - diff); }
        reverse_rnd_iterator operator-(const difference_type& diff) const { return reverse_rnd_iterator(ptr + diff); }
        reference operator[](const difference_type& offset) const { return *(*this + offset); }

        bool operator==(const reverse_rnd_iterator& it) const { return ptr == it.ptr; }
        bool operator!=(const reverse_rnd_iterator& it) const { return ptr != it.ptr; }
        bool operator<(const reverse_rnd_iterator& it) const { return ptr > it.ptr; }
        bool operator>(const reverse_rnd_iterator& it) const { return ptr < it.ptr; }
        bool operator>=(const reverse_rnd_iterator& it) const { return ptr <= it.ptr; }
        bool operator<=(const reverse_rnd_iterator& it) const { return ptr >= it.ptr; }
    };
}

#endif //TEMPLATE_ITERATORS_HPP
