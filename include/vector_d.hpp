//
// Created by adeon on 7/4/22.
//
// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#ifndef TEMPLATE_VECTOR_D_HPP
#define TEMPLATE_VECTOR_D_HPP

#include <cmath>
#include <iostream>

#include "consts.hpp"
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
    public:
        using iterator = bsd::rnd_iterator<T>;
        using const_iterator = bsd::rnd_iterator<const T>;
        using reverse_iterator = bsd::reverse_rnd_iterator<T>;
        using const_reverse_iterator = bsd::reverse_rnd_iterator<const T>;

        explicit vector_d(size_t size, const T& val=T()) : size_{size}, capacity_{size} {
            data_ = static_cast<T*>(::operator new(sizeof(T) * capacity_));

            for (size_t i = 0; i < size_; ++i) {
                new (data_ + i) T{val};
            }
        }

        vector_d() : vector_d(0) {};

        vector_d(const vector_d &v) : size_{v.size_}, capacity_{v.capacity_}{
            data_ = static_cast<T*>(::operator new(sizeof(T) * capacity_));

            for (size_t i = 0; i < size_; ++i) {
                new (data_ + i) T{v[i]};
            }
        }

        vector_d(vector_d&& v) noexcept : size_{v.size_}, capacity_{v.capacity_}{
            data_ = std::move(v.data());
            capacity_ = std::move(v.capacity());
            size_ = std::move(v.size());

            v.data_ = nullptr;
            v.capacity_ = 0;
            v.size_ = 0;
        }

        // This does not break everything anymore
        vector_d(std::initializer_list<T> l) : size_{l.size()}, capacity_{l.size()} {
            data_ = static_cast<T*>(::operator new(sizeof(T) * capacity_));
            size_t i = 0;
            for (auto it = l.begin(); it != l.end(); ++it) {
                new (data_ + i) T{*it};
                ++i;
            }
        }

        vector_d(iterator begin, iterator end) : size_{static_cast<size_t>(end - begin)}, capacity_{static_cast<size_t>(end - begin)} {
            data_ = static_cast<T*>(::operator new(sizeof(T) * capacity_));
            size_t i = 0;
            for (auto it = begin; it != end; ++it) {
                new (data_ + i) T{*it};
                ++i;
            }
        }

        ~vector_d() {
            for (size_t i = 0; i < size_; ++i) {
                data_[i].~T();
            }
            ::operator delete (data_);
        }

        [[nodiscard]] bool empty() {
            return (size_ == 0);
        }

        [[nodiscard]] size_t size() const{
            return size_;
        }

        [[nodiscard]] size_t capacity() const{
            return capacity_;
        }

        T& operator[](size_t pos) {
            return data_[pos];
        }

        T& operator[](size_t pos) const {
            return data_[pos];
        }

        vector_d& operator=(const vector_d &v) {
            vector_d<T> tmp{v};
            swap(tmp);
            return *this;
        }

        // Look into this as is same as move constructor!
        vector_d& operator=(vector_d&& v) {
            data_ = std::move(v.data());
            capacity_ = std::move(v.capacity());
            size_ = std::move(v.size());

            v.data_ = nullptr;
            v.capacity_ = 0;
            v.size_ = 0;

            return *this;
        }

        void reserve(size_t new_capacity) {
            if (new_capacity > capacity_) {
                T* new_data = static_cast<T*>(::operator new(sizeof(T) * new_capacity));

                for (size_t i = 0; i < size_; ++i) {
                    new (new_data+i) T{data_[i]};
                    data_[i].~T();
                }
                ::operator delete(data_);
                data_ = new_data;
                capacity_ = new_capacity;
            }
        }
        // Just reallocates the capacity to fit the size.
        void shrink_to_fit() {
            if (size_ < capacity_) {
                T* new_data = static_cast<T*>(::operator new(sizeof(T) * size_));

                for (size_t i = 0; i < size_; ++i) {
                    new (new_data+i) T{data_[i]};
                    data_[i].~T();
                }
                ::operator delete(data_);
                data_ = new_data;
                capacity_ = size_;
            }
        }

        // For now uses std::swap, but plan to change it to custom swap later
        void swap(vector_d<T> &v) {
            std::swap(size_, v.size_);
            std::swap(capacity_, v.capacity_);
            std::swap(data_, v.data_);
        }

        T& front() {
            return data_[0];
        }

        T& back() {
            return data_[size_ - 1];
        }

        T& at(size_t pos) {
            if (pos >= size_) {
                throw std::out_of_range("Vector index out of range :(");
            }
            return data_[pos];
        }

        // Returns data pointer if the size is != 0 else nullptr
        T* data() {
            return (size_ != 0) ? data_ : nullptr;
        }

        iterator begin() {
            return iterator(data_);
        }

        const_iterator cbegin() const {
            return const_iterator(data_);
        }

        iterator end() {
            return iterator(data_ + size_);
        }

        const_iterator cend() const {
            return const_iterator(data_ + size_);
        }

        reverse_iterator rbegin() {
            return reverse_iterator(data_ + size_ - 1);
        }

        const_reverse_iterator crbegin() const {
            return const_reverse_iterator(data_ + size_ - 1);
        }

        reverse_iterator rend() {
            return reverse_iterator(data_ - 1);
        }

        const_reverse_iterator crend() const {
            return const_reverse_iterator(data_ - 1);
        }

        void clear() {
            for (auto it = begin(); it != end(); ++it) {
                (*it).~T();
            }
            size_ = 0;
        }

        void push_back(T el) {
            if (size_ == capacity_) {
                reserve(std::max(CAP_MULTIPLIER * capacity_, capacity_ + 1));
            }
            new (data_ + (size_++)) T{el};
        }

        void pop_back() {
            data_[--size_].~T();
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
            if (size_ + count >= capacity_) {
                auto pos_idx = pos - begin();
                reserve(std::max(CAP_MULTIPLIER * capacity_, capacity_ + count));
                pos = iterator(data_ + pos_idx);
            }
            auto it = end();
            if (it == pos) {
                for (size_t i = 0; i < count; ++i) {
                    data_[size_] = el;
                    size_++;
                }
            } else {
                --it;
                for (int i = static_cast<int>(count) - 1; i >= 0; --i) {
                    data_[size_ + i] = T{*it};
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
                size_ += count;
            }

            return (end() - (pos - count + 1) > 1) ? pos - count : pos;
        }

        template<typename ... Args>
        void emplace_back(Args&&... args) {
            if (size_ == capacity_) {
                reserve(std::max(CAP_MULTIPLIER * capacity_, capacity_ + 1));
            }
            new (data_ + (size_++)) T{std::forward<Args>(args)...};
        }

        /*
         * Allocates new memory block if the old one is too small.
         * Also uses the iterator instead of const_iterator for implementation simplicity and similatiry to insert
         * Returns iterator to the emplaced element
         */
        template<typename ... Args>
        iterator emplace(const_iterator pos, Args&&... args) {
            iterator npos = (begin() + (pos - cbegin()));
            if (size_ >= capacity_) {
                auto pos_idx = pos - cbegin();
                reserve(std::max(CAP_MULTIPLIER * capacity_, capacity_ + 1));
                npos = iterator(data_ + pos_idx);
            }
            auto it = end();
            if (it == npos) {
                new (data_ + (size_++)) T{std::forward<Args>(args)...};
            } else {
                --it;
                data_[size_] = T{*it};
                while (it > npos - 1) {
                    *it = *(it - 1);
                    --it;
                }
                new (data_ + (npos - begin())) T{std::forward<Args>(args)...};
                ++size_;
            }

            return iterator(begin() + (npos - begin()));
        }
        // Destroy the erased element and move others a position down.
        iterator erase(iterator pos) {
            if (pos == end()) {
                return end();
            }
            auto it = begin() + (pos - begin());
            // If element is last, just destroy it
            if (it == end() - 1) {
                data_[--size_].~T();
            } else {
                while (it != end() - 1) {
                    *it = *(it + 1);
                    ++it;
                }
                data_[--size_].~T();
            }

            return pos;
        }

        void resize(size_t count) {
            if (count < size_ ) {
                for (size_t i = size_ - 1; i > count - 1; --i) {
                    data_[i].~T();
                }
                size_ = count;
            } else if (count < capacity_) {
                while (size_ < count) {
                    new (data_ + size_) T{};
                    ++size_;
                }
            } else if (count > capacity_) {
                reserve(count);
                while (size_ < capacity_) {
                    new (data_ + size_) T{};
                    ++size_;
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
        size_t size_, capacity_;
        T* data_;
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