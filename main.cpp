// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include <iostream>
#include <vector>

#include "ratiod_t.hpp"
#include "vector_d.hpp"

template<typename T>
void prnt_vec(const bsd::vector_d<T> &vec) {
    for (auto i = vec.cbegin(); i != vec.cend(); ++i) {
        std::cout << *i << ", ";
    }
    std::cout << "\n";
}

template<typename T>
void prnt_vec_info(const bsd::vector_d<T> &vec) {
    prnt_vec(vec);
    std::cout << "Size: " << vec.size() << " Capacity: " << vec.capacity() << std::endl;
}

template<typename T>
void prnt_stdvec_info(const std::vector<T> &vec) {
    for (auto i = vec.cbegin(); i != vec.cend(); ++i) {
        std::cout << *i << ", ";
    }
    std::cout << "\n";
    std::cout << "Size: " << vec.size() << " Capacity: " << vec.capacity() << std::endl;
}

int main() {
    std::cout << "v1/v2" << std::endl;
    bsd::vector_d<int> v1(10);
    bsd::vector_d<int> v2(5);
    prnt_vec(v1);
    prnt_vec(v2);

    std::cout << "v1/v2 after v1=v2" << std::endl;
    v1 = v2;
    prnt_vec(v1);
    prnt_vec(v2);

    std::cout << "v3{v1}" << std::endl;
    v1[2] = 123;
    bsd::vector_d<int> v3{v1};
    prnt_vec(v3);

    std::cout << "v3 reserve" << std::endl;
    v3.reserve(100);
    prnt_vec(v3);
    std::cout << v3.size() << " " << v3.capacity() << std::endl;

    bsd::vector_d<int> v4;
    std::cout << "v4 push back:" << std::endl;
    std::cout << "Size: " << v4.size() << " Capacity: " << v4.capacity() << std::endl;
    for (int i = 0; i < 10; i++) {
        v4.push_back(i);
        prnt_vec(v4);
        std::cout << "Size: " << v4.size() << " Capacity: " << v4.capacity() << std::endl;
    }
    std::cout << "v4 pop back:" << std::endl;
    for (int i = 0; i < 5; i++) {
        v4.pop_back();
        prnt_vec(v4);
        std::cout << "Size: " << v4.size() << " Capacity: " << v4.capacity() << std::endl;
    }
    std::cout << "v4 shrink_to_fit:" << std::endl;
    v4.shrink_to_fit();
    prnt_vec(v4);
    std::cout << "Size: " << v4.size() << " Capacity: " << v4.capacity() << std::endl;

    std::cout << "aftr push:" << std::endl;
    v4.push_back(1);
    prnt_vec(v4);
    std::cout << "Size: " << v4.size() << " Capacity: " << v4.capacity() << std::endl;

    std::cout << "Reverse iterator equality test:" << std::endl;
    std::vector<int> vecc{3, 4, 6, 1, 0, 2};
    auto pr = vecc.rend();
    --pr;
    std::cout << "Simple vector: ";
    for (auto i = vecc.rbegin(); i != vecc.rend(); ++i) {
        std::cout << *i << *pr << (i < pr) << i - pr << ";";
    }
    std::cout << "\n";

//    bsd::vector_d<int> veccc{3, 4, 6, 1, 0, 2};
//    auto pr2 = veccc.rend();
//    pr2--;
//    std::cout << "BASED vector: ";
//    for (auto i = veccc.rbegin(); i != veccc.rend(); ++i) {
//        std::cout << *i << *pr2 << (i < pr2) << i - pr2 << ";";
//    }
//    std::cout << "\n";
//
    std::cout << "Clear:" << std::endl;
    std::cout << "before: ";
    prnt_vec_info(v4);
    std::cout << "after: ";
    v4.clear();
    prnt_vec_info(v4);

    std::cout << "Insert(tested all possible cases):" << std::endl;
    v4.push_back(3);
    v4.push_back(8);
    v4.push_back(5);
    v4.push_back(9);
    std::cout << "before: ";
    prnt_vec_info(v4);
    std::cout << "after: ";
    v4.shrink_to_fit();
    v4.insert(v4.begin() + 3, 8 ,0);
    prnt_vec_info(v4);

    std::cout << "emplace_back:" << std::endl;
    bsd::vector_d<bsd::ratio_d_t> v5;
    v5.emplace_back(3, 4);
    v5.emplace_back(9, 6);
    v5.emplace_back(4, 6);
    prnt_vec_info(v5);
    std::cout << "emplace:" << std::endl;
    v5.emplace(v5.cbegin() + 2, 1, 10);
    prnt_vec_info(v5);

    std::cout << "erase:" << std::endl;
    std::cout << "before: ";
    prnt_vec_info(v5);
    v5.erase(v5.begin());
    std::cout << "after: ";
    prnt_vec_info(v5);

    std::cout << "resize: " << std::endl;
    bsd::vector_d<int> l;
    l.push_back(2);
    l.push_back(2);
    l.push_back(2);
    prnt_vec_info(l);
    l.resize(1);
    l.resize(3);
    prnt_vec_info(l);

    std::cout << "assign:" << std::endl;
    bsd::vector_d<int> r{};
    for (size_t i = 0; i < 5; ++i) {
        r.push_back(i);
    }
    std::cout << "before: ";
    prnt_vec_info(r);
    r.assign(10, 228);
    std::cout << "after: ";
    prnt_vec_info(r);

    return 0;
}