// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "ratiod_t.hpp"

// Math function implementation
bsd::ratio_d_t bsd::pow(const ratio_d_t& rt, int n) {
    ratio_d_t res{rt};
    if (n < 0) {
        res.inverse_base();
        n = std::abs(n);
    }
    int num = res.m_num;
    int den = res.m_den;

    for (int i = 1; i < n; i++) {
        res.m_num *= num;
        res.m_den *= den;
    }

    return res;
}

bsd::ratio_d_t bsd::ceil(const ratio_d_t& rt) {
    ratio_d_t res{rt};
    while (res.m_num % res.m_den != 0) {
        ++res.m_num;
    }
    res.reduce();
    return res;
}

bsd::ratio_d_t bsd::floor(const ratio_d_t& rt) {
    ratio_d_t res{rt};
    while (res.m_num % res.m_den != 0) {
        --res.m_num;
    }
    res.reduce();
    return res;
}

bsd::ratio_d_t bsd::trunc(const ratio_d_t& rt) {
    return (rt.is_positive()) ? floor(rt): ceil(rt);
}
// This is very fucking stupid
bsd::ratio_d_t bsd::round(const ratio_d_t& rt) {
    ratio_d_t res{rt};

    double temp = std::abs(res.m_num);
    while (temp > res.m_den) {
        temp -= res.m_den;
    }

    if (temp > res.m_den / 2.0) {
        res.round_ceil();
    } else if (temp < res.m_den / 2.0) {
        res.round_floor();
    } else {
        return (res.is_positive()) ? ceil(res) : floor(res);
    }
    return res;
}

// if == return first arg
bsd::ratio_d_t bsd::min(const bsd::ratio_d_t& rt1, const bsd::ratio_d_t& rt2) {
    return (rt1 <= rt2) ? bsd::ratio_d_t{rt1} : bsd::ratio_d_t{rt2};
}

bsd::ratio_d_t bsd::max(const bsd::ratio_d_t& rt1, const bsd::ratio_d_t& rt2) {
    return (rt1 < rt2) ? bsd::ratio_d_t{rt2} : bsd::ratio_d_t{rt1};
}

bsd::ratio_d_t bsd::abs(const bsd::ratio_d_t& rt) {
    bsd::ratio_d_t res{rt};
    res.abs();
    return res;
}
