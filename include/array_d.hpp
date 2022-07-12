//
// Created by adeon on 7/11/22.
//

#ifndef TEMPLATE_ARRAY_D_HPP
#define TEMPLATE_ARRAY_D_HPP

#include <iostream>

#include "iterators.hpp"

namespace bsd {
    template<typename T, size_t N>
    class array_d {
        using iterator = bsd::rnd_iterator<T>;
        using const_iterator = bsd::rnd_iterator<const T>;
        using reverse_iterator = bsd::rnd_iterator<T>;
        using const_reverse_iterator = bsd::rnd_iterator<const T>;
    public:
        /*
         * For now the constructor just ignores the arr[N+x] elements and does not do compile time checks
         * Also inserts the given elements and constructs/reconstructs in case of basic types like int, the rest.
         */
        array_d(std::initializer_list<T> l) {
            auto it = l.begin();
            auto it_end = l.end();
            for (size_t i = 0; i < N; ++i) {
                if (it == it_end) {
                    data_[i] = T{};
                } else {
                    data_[i] = *it;
                    ++it;
                }
            }
        }

        // Call a destructor for each element
        ~array_d() {
            for (size_t i = 0; i < N; ++i) {
                data_[i].~T();
            }
        };

        array_d& operator=(const array_d<T, N>& rhs) {
            for (size_t i = 0; i < N; ++i) {
                data_[i] = rhs[i];
            }
            return *this;
        }

        T& at(size_t pos) {
            if (pos >= N) {
                throw std::out_of_range("array index out og range");
            }
            return data_[pos];
        }

        T& operator[](size_t pos) {
            return data_[pos];
        }

        const T& operator[](size_t pos) const {
            return data_[pos];
        }

        T& front() {
            return data_[0];
        }

        T& back() {
            return data_[N - 1];
        }

        const T& front() const {
            return data_[0];
        }

        const T& back() const {
            return data_[N - 1];
        }

        T* data() {
            return data_;
        }

        iterator begin() {
            return iterator(data_);
        }

        const_iterator cbegin() const {
            return const_iterator(data_);
        }

        iterator end() {
            return iterator(data_ + N);
        }

        const_iterator cend() const {
            return const_iterator(data_ + N);
        }

        reverse_iterator rbegin() {
            return reverse_iterator(data_ + N - 1);
        }

        const_reverse_iterator crbegin() const {
            return const_reverse_iterator(data_ + N - 1);
        }

        reverse_iterator rend() {
            return reverse_iterator(data_ - 1);
        }

        const_reverse_iterator crend() const {
            return const_reverse_iterator(data_ - 1);
        }

        [[nodiscard]] bool is_empty() const {
            return (N == 0);
        }

        [[nodiscard]] size_t size() const {
            return N;
        }
        // In arrays, msx_size returns the original array size
        [[nodiscard]] size_t max_size() const {
            return N;
        }

        void fill(const T& val) {
            for (auto it = begin(); it != end(); ++it) {
                *it = val;
            }
        }
        // TODO insert my bsd::swap
        void swap(array_d& arr) {
            std::swap(data_, arr.data_);
        }

    private:
        T data_[N];
    };

    template< class T, std::size_t N >
    inline bool operator==(const bsd::array_d<T, N>& lhs, const bsd::array_d<T, N>& rhs ) {
        for (size_t i = 0; i < N; ++i) {
            if (lhs[i] != rhs[i]) return false;
        }
        return true;
    }

    template< class T, std::size_t N >
    inline bool operator!=(const bsd::array_d<T, N>& lhs, const bsd::array_d<T, N>& rhs ) {
        return !(lhs == rhs);
    }

    template< class T, std::size_t N >
    inline bool operator<(const bsd::array_d<T, N>& lhs, const bsd::array_d<T, N>& rhs ) {
        for (size_t i = 0; i < N; ++i) {
            if (lhs[i] >= rhs[i]) return false;
        }
        return true;
    }

    template< class T, std::size_t N >
    inline bool operator<=(const bsd::array_d<T, N>& lhs, const bsd::array_d<T, N>& rhs ) {
        for (size_t i = 0; i < N; ++i) {
            if (lhs[i] > rhs[i]) return false;
        }
        return true;
    }

    template< class T, std::size_t N >
    inline bool operator>(const bsd::array_d<T, N>& lhs, const bsd::array_d<T, N>& rhs ) {
        for (size_t i = 0; i < N; ++i) {
            if (lhs[i] <= rhs[i]) return false;
        }
        return true;
    }

    template< class T, std::size_t N >
    inline bool operator>=(const bsd::array_d<T, N>& lhs, const bsd::array_d<T, N>& rhs ) {
        for (size_t i = 0; i < N; ++i) {
            if (lhs[i] < rhs[i]) return false;
        }
        return true;
    }
}


#endif //TEMPLATE_ARRAY_D_HPP
