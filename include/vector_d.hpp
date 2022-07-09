//
// Created by adeon on 7/4/22.
//
// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#ifndef TEMPLATE_VECTOR_D_HPP
#define TEMPLATE_VECTOR_D_HPP

#include <cmath>
#include <iostream>
#include "iterators.hpp"

/*
 * DISCLAIMER:
 * This vector is far from perfect and was made with study purposes in mind.
 * There arent a lot of function overloads because they all are quite similar so I was
 * just making the main ones in order to learn.
 */

namespace bsd {
    template<typename T>
    class vector_d {
        static constexpr size_t CAP_MULTIPLIER = 2; // fucking stupid
    public:
        using iterator = bsd::rnd_iterator<T>;
        using const_iterator = bsd::rnd_iterator<const T>;
        using reverse_iterator = bsd::reverse_rnd_iterator<T>;
        using const_reverse_iterator = bsd::reverse_rnd_iterator<const T>;

        explicit vector_d(size_t size, const T& val=T()) : m_size{size}, m_capacity{size} {
            m_data = static_cast<T*>(::operator new(sizeof(T) * m_capacity));

            for (size_t i = 0; i < m_size; ++i) {
                new (m_data + i) T{val};
            }
        }

        vector_d() : vector_d(0) {};

        vector_d(const vector_d &v) : m_size{v.m_size}, m_capacity{v.m_capacity}{
            m_data = static_cast<T*>(::operator new(sizeof(T) * m_capacity));

            for (size_t i = 0; i < m_size; ++i) {
                new (m_data + i) T{v[i]};
            }
        }

        vector_d(vector_d&& v) : m_size{v.m_size}, m_capacity{v.m_capacity}{
            m_data = std::move(v.data());
            m_capacity = std::move(v.capacity());
            m_size = std::move(v.size());

            v.m_data = nullptr;
            v.m_capacity = 0;
            v.m_size = 0;
        }

        // This does not break everything anymore
        vector_d(std::initializer_list<T> l) : m_size{l.size()}, m_capacity{l.size()} {
            m_data = static_cast<T*>(::operator new(sizeof(T) * m_capacity));
            size_t i = 0;
            for (auto it = l.begin(); it != l.end(); ++it) {
                new (m_data + i) T{*it};
                ++i;
            }
        }

        ~vector_d() {
            for (size_t i = 0; i < m_size; ++i) {
                m_data[i].~T();
            }
            ::operator delete (m_data);
        }

        [[nodiscard]] bool empty() {
            return (m_size == 0);
        }

        [[nodiscard]] size_t size() const{
            return m_size;
        }

        [[nodiscard]] size_t capacity() const{
            return m_capacity;
        }

        T& operator[](size_t pos) {
            return m_data[pos];
        }

        T& operator[](size_t pos) const {
            return m_data[pos];
        }

        vector_d& operator=(const vector_d &v) {
            vector_d<T> tmp{v};
            swap(tmp);
            return *this;
        }

        void reserve(size_t new_capacity) {
            if (new_capacity > m_capacity) {
                T* new_data = static_cast<T*>(::operator new(sizeof(T) * new_capacity));

                for (size_t i = 0; i < m_size; ++i) {
                    new (new_data+i) T{m_data[i]};
                    m_data[i].~T();
                }
                ::operator delete(m_data);
                m_data = new_data;
                m_capacity = new_capacity;
            }
        }
        // Just reallocates the capacity to fit the size.
        void shrink_to_fit() {
            if (m_size < m_capacity) {
                T* new_data = static_cast<T*>(::operator new(sizeof(T) * m_size));

                for (size_t i = 0; i < m_size; ++i) {
                    new (new_data+i) T{m_data[i]};
                    m_data[i].~T();
                }
                ::operator delete(m_data);
                m_data = new_data;
                m_capacity = m_size;
            }
        }

        // For now uses std::swap, but plan to change it to custom swap later
        void swap(vector_d<T> &v) {
            std::swap(m_size, v.m_size);
            std::swap(m_capacity, v.m_capacity);
            std::swap(m_data, v.m_data);
        }

        T& front() {
            return m_data[0];
        }

        T& back() {
            return m_data[m_size - 1];
        }

        T& at(size_t pos) {
            if (pos >= m_size) {
                throw std::out_of_range("Vector index out of range :(");
            }
            return m_data[pos];
        }

        // Returns data pointer if the size is != 0 else nullptr
        T* data() {
            return (m_size != 0) ? m_data : nullptr;
        }

        iterator begin() {
            return iterator(m_data);
        }

        const_iterator cbegin() const {
            return const_iterator(m_data);
        }

        iterator end() {
            return iterator(m_data + m_size);
        }

        const_iterator cend() const {
            return const_iterator(m_data + m_size);
        }

        reverse_iterator rbegin() {
            return reverse_iterator(m_data + m_size - 1);
        }

        const_reverse_iterator crbegin() const {
            return const_reverse_iterator(m_data + m_size - 1);
        }

        reverse_iterator rend() {
            return reverse_iterator(m_data - 1);
        }

        const_reverse_iterator crend() const {
            return const_reverse_iterator(m_data - 1);
        }

        void clear() {
            for (auto it = begin(); it != end(); ++it) {
                (*it).~T();
            }
            m_size = 0;
        }

        void push_back(T el) {
            if (m_size == m_capacity) {
                reserve(std::max(CAP_MULTIPLIER * m_capacity, m_capacity + 1));
            }
            new (m_data + (m_size++)) T{el};
        }

        void pop_back() {
            m_data[--m_size].~T();
        }

        // During reserve operation copies 2 times.
        iterator insert(iterator pos, const T& el) {
            return insert(pos, 1, el);
        }
        /*
         * Allocates new memory block if the old one is too small.
         * Returns iterator to the inserted element
         */
        iterator insert(iterator pos, size_t count, const T& el) {
            if (m_size + count >= m_capacity) {
                auto pos_idx = pos - begin();
                reserve(std::max(CAP_MULTIPLIER * m_capacity, m_capacity + count));
                pos = iterator(m_data + pos_idx);
            }
            auto it = end();
            if (it == pos) {
                for (size_t i = 0; i < count; ++i) {
                    m_data[m_size] = el;
                    m_size++;
                }
            } else {
                --it;
                for (int i = static_cast<int>(count) - 1; i >= 0; --i) {
                    m_data[m_size+i] = T{*it};
                    if (it == begin()) break;
                    if (count != 1) --it;
                }
                while (it > pos + count - 1) {
                    *it = *(it - count);
                    --it;
                }
                for (size_t i = 0; i < count; ++i) {
                    *pos = el;
                    ++pos;
                }
                m_size += count;
            }

            return pos - count;
        }

        template<typename ... Args>
        void emplace_back(Args&&... args) {
            if (m_size == m_capacity) {
                reserve(std::max(CAP_MULTIPLIER * m_capacity, m_capacity + 1));
            }
            new (m_data + (m_size++)) T{std::forward<Args>(args)...};
        }

        /*
         * Allocates new memory block if the old one is too small.
         * Also uses the iterator instead of const_iterator for implementation simplicity and similatiry to insert
         * Returns iterator to the emplaced element
         */
        template<typename ... Args>
        iterator emplace(const_iterator pos, Args&&... args) {
            iterator npos = (begin() + (pos - cbegin()));
            if (m_size >= m_capacity) {
                auto pos_idx = pos - cbegin();
                reserve(std::max(CAP_MULTIPLIER * m_capacity, m_capacity + 1));
                npos = iterator(m_data + pos_idx);
            }
            auto it = end();
            if (it == npos) {
                new (m_data + (m_size++)) T{std::forward<Args>(args)...};
            } else {
                --it;
                m_data[m_size] = T{*it};
                while (it > npos - 1) {
                    *it = *(it - 1);
                    --it;
                }
                new (m_data + (npos - begin())) T{std::forward<Args>(args)...};
                ++m_size;
            }

            return iterator(begin() + (npos - begin()));
        }

        iterator erase(iterator pos) {
            if (pos == end()) {
                return end();
            }
            auto it = begin() + (pos - begin());
            if (it == end() - 1) {
                m_data[--m_size].~T();
            } else {
                while (it != end() - 1) {
                    *it = *(it + 1);
                    ++it;
                }
                m_data[--m_size].~T();
            }

            return pos;
        }

        void resize(size_t count) {
            if ( count < m_size ) {
                for (size_t i = m_size - 1; i > count - 1; --i) {
                    m_data[i].~T();
                }
                m_size = count;
            } else if (count < m_capacity) {
                while (m_size < count) {
                    new (m_data + m_size) T{};
                    ++m_size;
                }
            } else if (count > m_capacity) {
                reserve(count);
                while (m_size < m_capacity) {
                    new (m_data + m_size) T{};
                    ++m_size;
                }
            }
        }
        // Just creates a new vector and swaps it with the current one.
        void assign(size_t count, const T& value) {
            vector_d<T> v;
            for (size_t i = 0; i < count; ++i) {
                v.push_back(value);
            }
            swap(v);
        }

    private:
        size_t m_size, m_capacity;
        T* m_data;
    };

    template<typename T>
    bool operator==(const vector_d<T>& lhs, const vector_d<T>& rhs) {
        if (lhs.size() != rhs.size()) {
            return false;
        }
        for (size_t i = 0; i < lhs.size(); ++i) {
            if (lhs[i] != rhs[i]) {
                return false;
            }
        }
        return true;
    }

    template <typename T>
    bool operator!=(const vector_d<T>& lhs, const vector_d<T>& rhs) {
        return !(lhs == rhs);
    }
}

#endif //TEMPLATE_VECTOR_D_HPP