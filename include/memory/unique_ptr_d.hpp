//
// Created by adeon on 7/13/22.
//

#ifndef TEMPLATE_UNIQUE_PTR_D_HPP
#define TEMPLATE_UNIQUE_PTR_D_HPP

namespace bsd {
    template<typename T>
    class unique_ptr_d {
        using pointer = T*;
    public:
        unique_ptr_d() : ptr_{nullptr} {}

        explicit unique_ptr_d(T* arg) : ptr_{arg} {}

        unique_ptr_d(unique_ptr_d&& upd) noexcept {
            ptr_ = upd->ptr;
            upd->ptr = nullptr;
        }

        unique_ptr_d(const unique_ptr_d& upd) = delete;

        ~unique_ptr_d() {
            delete(ptr_);
        }

        unique_ptr_d& operator=(const unique_ptr_d& upd) = delete;

        unique_ptr_d& operator=(unique_ptr_d&& upd) noexcept {
            ptr_ = upd->ptr;
            upd->ptr = nullptr;
            return *this;
        };

        T* release() {
            T* old_ptr = ptr_;
            ptr_ = nullptr;
            return old_ptr;
        }
        // For now without the deleter
        T* reset(pointer ptr = pointer()) {
            pointer old_ptr = ptr_;
            ptr_ = ptr;
            delete(old_ptr);
        }
        // TODO: Swap deletors as well
        unique_ptr_d swap(unique_ptr_d& upd) {
            T* swap_ptr = ptr_;
            ptr_ = upd.ptr_;
            upd.ptr_ = swap_ptr;
        }

        pointer get() {
            return ptr_;
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
    };
}

#endif //TEMPLATE_UNIQUE_PTR_D_HPP
