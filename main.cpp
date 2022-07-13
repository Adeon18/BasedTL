// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include <iostream>
#include <vector>
#include <array>
#include <memory>

#include "ratiod_t.hpp"
#include "vector_d.hpp"
#include "array_d.hpp"
#include "memory/unique_ptr_d.hpp"

void unique_ptr_test(std::unique_ptr<bsd::ratio_d_t> & a) {
    std::cout << *a << std::endl;
}

void unique_ptr_test_move(std::unique_ptr<bsd::ratio_d_t> a) {
    std::cout << *a << std::endl;
}

void unique_ptr_test(bsd::unique_ptr_d<bsd::ratio_d_t> & a) {
    std::cout << *a << std::endl;
}

void unique_ptr_test_move(bsd::unique_ptr_d<bsd::ratio_d_t> a) {
    std::cout << *a << std::endl;
}


int main() {

    std::unique_ptr<bsd::ratio_d_t> p1(new bsd::ratio_d_t(1, 3));

    unique_ptr_test(p1);
    unique_ptr_test_move(std::move(p1));



    return 0;
}