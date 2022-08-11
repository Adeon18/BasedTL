//
// Created by adeon on 7/13/22.
//

#ifndef TEMPLATE_UNIQUE_PTR_D_HPP
#define TEMPLATE_UNIQUE_PTR_D_HPP

namespace bsd {
    // For no only supports default deleter
    template<typename T, typename D=std::default_delete<T>>
    class unique_ptr_d {
        using pointer = T*;
    public:
        unique_ptr_d() : ptr_{nullptr} {}

        explicit unique_ptr_d(T* arg) : ptr_{arg} {}

        unique_ptr_d(unique_ptr_d&& upd) noexcept {
            ptr_ = upd.ptr_;
            upd.ptr_ = nullptr;
        }

        unique_ptr_d(const unique_ptr_d& upd) = delete;

        ~unique_ptr_d() {
            get_deleter()(ptr_);
        }

        unique_ptr_d& operator=(const unique_ptr_d& upd) = delete;

        unique_ptr_d& operator=(unique_ptr_d&& upd) noexcept {
            ptr_ = upd.ptr_;
            upd.ptr_ = nullptr;
            return *this;
        };

        T* release() {
            T* old_ptr = ptr_;
            ptr_ = nullptr;
            return old_ptr;
        }
        // For now without the deleter
        void reset(pointer ptr = pointer()) {
            pointer old_ptr = ptr_;
            ptr_ = ptr;
            get_deleter()(old_ptr);
        }
        // TODO: Swap deletors as well
        void swap(unique_ptr_d& upd) {
            T* swap_ptr = ptr_;
            ptr_ = upd.ptr_;
            upd.ptr_ = swap_ptr;

        }

        pointer get() const noexcept {
            return ptr_;
        }

        D& get_deleter() noexcept {
            return deleter_;
        }

        const D& get_deleter() const noexcept {
            return deleter_;
        }

        explicit operator bool() const noexcept {
            return (get() != nullptr);
        }

        T operator *() const {
            return *get();
        }

        pointer operator ->() const noexcept {
            return get();
        }

    private:
        T* ptr_;
        D deleter_;
    };

    template<typename T1, typename D1, typename T2, typename D2>
    bool operator ==(const unique_ptr_d<T1, D1>& lhs, const unique_ptr_d<T2, D2>& rhs) {
        return lhs.get() == rhs.get();
    }

    template<typename T1, typename D1, typename T2, typename D2>
    bool operator !=(const unique_ptr_d<T1, D1>& lhs, const unique_ptr_d<T2, D2>& rhs) {
        return !(lhs == rhs);
    }

    template<typename T1, typename D1, typename T2, typename D2>
    bool operator <(const unique_ptr_d<T1, D1>& lhs, const unique_ptr_d<T2, D2>& rhs) {
        return lhs.get() < rhs.get();
    }

    template<typename T1, typename D1, typename T2, typename D2>
    bool operator >=(const unique_ptr_d<T1, D1>& lhs, const unique_ptr_d<T2, D2>& rhs) {
        return !(lhs < rhs);
    }

    template<typename T1, typename D1, typename T2, typename D2>
    bool operator >(const unique_ptr_d<T1, D1>& lhs, const unique_ptr_d<T2, D2>& rhs) {
        return rhs < lhs;
    }

    template<typename T1, typename D1, typename T2, typename D2>
    bool operator <=(const unique_ptr_d<T1, D1>& lhs, const unique_ptr_d<T2, D2>& rhs) {
        return !(lhs > rhs);
    }

    template<typename T, typename D>
    bool operator ==(const unique_ptr_d<T, D>& lhs, std::nullptr_t) {
        return !lhs.get();
    }

    template<typename T, typename D>
    bool operator !=(const unique_ptr_d<T, D>& lhs, std::nullptr_t) {
        return !(lhs == nullptr);
    }

    template<typename T, typename D>
    bool operator <(const unique_ptr_d<T, D>& lhs, std::nullptr_t) {
        return lhs.get() < nullptr;
    }

    template<typename T, typename D>
    bool operator >=(const unique_ptr_d<T, D>& lhs, std::nullptr_t) {
        return !(lhs < nullptr);
    }

    template<typename T, typename D>
    bool operator >(const unique_ptr_d<T, D>& lhs, std::nullptr_t) {
        return (lhs.get() > nullptr);
    }

    template<typename T, typename D>
    bool operator <=(const unique_ptr_d<T, D>& lhs, std::nullptr_t) {
        return !(lhs > nullptr);
    }

    template<typename T, typename D>
    bool operator ==(nullptr_t, unique_ptr_d<T, D>& rhs) {
        return !rhs.get();
    }

    template<typename T, typename D>
    bool operator !=(nullptr_t, unique_ptr_d<T, D>& rhs) {
        return !(rhs == nullptr);
    }

    template<typename T, typename D>
    bool operator <(nullptr_t, unique_ptr_d<T, D>& rhs) {
        return nullptr < rhs;
    }

    template<typename T, typename D>
    bool operator >=(nullptr_t, unique_ptr_d<T, D>& rhs) {
        return !(nullptr < rhs);
    }

    template<typename T, typename D>
    bool operator >(nullptr_t, unique_ptr_d<T, D>& rhs) {
        return (rhs.get() < nullptr);
    }

    template<typename T, typename D>
    bool operator <=(nullptr_t, unique_ptr_d<T, D>& rhs) {
        return !(rhs < nullptr);
    }
}

#endif //TEMPLATE_UNIQUE_PTR_D_HPP
