// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include <iostream>
#include <vector>
#include <array>

#include "ratiod_t.hpp"
#include "vector_d.hpp"
#include "array_d.hpp"



int main() {

    std::array<int, 4> a{1, 2, 3};
    std::array<int, 3> a2{1, 2};

    a = a2;
    return 0;
}