// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
//
// Created by adeon on 6/24/22.
//

#ifndef TEMPLATE_RATIOD_T_HPP
#define TEMPLATE_RATIOD_T_HPP
#include <iostream>

namespace bsd {
    class ratio_d_t {
    public:
        ratio_d_t(int num, int den): m_num{num}, m_den{den} {
            manage_edge_cases();
            manage_signs();
            reduce();
        }

        // One argument means only the numerator is given
        explicit ratio_d_t(int num): ratio_d_t(num, 1) {}

        ratio_d_t(): m_num{1}, m_den{1} {}

        ~ratio_d_t() = default;

        void set_num(int num) {
            m_num = num;
            reduce();
        }

        void set_den(int den) {
            m_den = den;
            reduce();
        }

        [[nodiscard]] int get_num() const {
            return m_num;
        }

        [[nodiscard]] int get_den() const {
            return m_den;
        }
        // Is POSITIVE, not 0
        [[nodiscard]] bool is_positive() const {
            return (m_num > 0);
        }

        [[nodiscard]] std::string get_string() const {
            if (m_num == 0 && m_den == 0) {
                return "NaN";
            } else if (m_num == 1 && m_den == 0) {
                return "+inf";
            } else if (m_num == -1 && m_den == 0) {
                return "-inf";
            }
            return std::to_string(m_num) + "/" + std::to_string(m_den);
        }
        /*
         * Allows you to inverse the ratio because why not:)
         * Also swaps 2 numbers without the third variable because Gameloft moment
         */
        void inverse_base() {
            m_num *= m_den;
            m_den = m_num / m_den;
            m_num /= m_den;
            manage_signs();
        }
        /*
         * Resets the ration to 1/1, made for keeping encapsulation for some methods like >>
         * Helps know the ration state
         */
        void reset() {
            m_num = 1;
            m_den = 1;
        }

        /*
         * Just makes the abs value of the current ratio
         * Can be used like this or is used in bsd::abs
         */
        void abs() {
            m_num = std::abs(m_num);
        }

        ratio_d_t& operator+=(const ratio_d_t& rt) {
            m_num = m_num * rt.m_den + rt.m_num * m_den;
            m_den *= rt.m_den;
            reduce();
            return *this;
        }
        // What the fuck
        ratio_d_t& operator+=(int n) {
            *this += ratio_d_t{n, 1};
            return *this;
        }
        /*
         * Adds 1 to the whole rational number/ like += 1
         */
        ratio_d_t& operator++() {
            *this += 1;
            return *this;
        }

        ratio_d_t operator++(int) {
            ratio_d_t res{*this};
            ++*this;
            return res;
        }

        ratio_d_t& operator--() {
            *this -= 1;
            return *this;
        }

        ratio_d_t operator--(int) {
            ratio_d_t res{*this};
            --*this;
            return res;
        }

        ratio_d_t& operator-=(const ratio_d_t& rt) {
            m_num = m_num * rt.m_den - rt.m_num * m_den;
            m_den *= rt.m_den;
            reduce();
            return *this;
        }

        ratio_d_t& operator-=(int n) {
            *this -= ratio_d_t{n, 1};
            return *this;
        }

        ratio_d_t& operator*=(const ratio_d_t& rt) {
            m_num = m_num * rt.m_num;
            m_den = m_den * rt.m_den;
            manage_signs();
            reduce();
            return *this;
        }

        ratio_d_t& operator*=(int n) {
            *this *= ratio_d_t{n, 1};
            return *this;
        }

        ratio_d_t& operator/=(const ratio_d_t& rt) {
            *this *= ratio_d_t{rt.m_den, rt.m_num};
            return *this;
        }

        ratio_d_t& operator/=(int n) {
            *this *= ratio_d_t{1, n};
            return *this;
        }
        // Comparisons
        bool operator==(const ratio_d_t& rt) const{
            return (m_num == rt.m_num && m_den == rt.m_den);
        }

        bool operator==(int n) const{
            return (m_num == n && m_den == 1);
        }
        // EHH??????
        bool operator!=(const ratio_d_t& rt) const{
            return !(*this == rt);  // wtf...
        }

        bool operator!=(int n) const{
            return !(*this == n);  // wtf...
        }

        bool operator>(const ratio_d_t& rt) const{
            return (m_num * rt.m_den > m_den * rt.m_num);
        }

        bool operator>(int n) const{
            return (m_num > n * m_den);
        }

        bool operator>=(const ratio_d_t& rt) const{
            return (m_num * rt.m_den >= m_den * rt.m_num);
        }

        bool operator>=(int n) const{
            return (m_num >= n * m_den);
        }
        bool operator<(const ratio_d_t& rt) const{
            return (m_num * rt.m_den < m_den * rt.m_num);
        }

        bool operator<(int n) const{
            return (m_num < n * m_den);
        }

        bool operator<=(const ratio_d_t& rt) const{
            return (m_num * rt.m_den <= m_den * rt.m_num);
        }

        bool operator<=(int n) const{
            return (m_num <= n * m_den);
        }
        // Math functions
        friend ratio_d_t pow(const ratio_d_t& rt, int n);
        friend ratio_d_t ceil(const ratio_d_t& rt);
        friend ratio_d_t floor(const ratio_d_t& rt);
        friend ratio_d_t trunc(const ratio_d_t& rt);
        friend ratio_d_t round(const ratio_d_t& rt);

    private:
        int m_num, m_den;

        // Manages inf and NaN
        void manage_edge_cases() {
            if (m_den == 0 && m_num != 0) {
                m_num = 1;
            } else if (m_den != 0 && m_num == 0) {
                m_den = 1;
            }
        }

        void manage_signs() {
            if (m_num < 0 && m_den < 0) {
                m_num = std::abs(m_num);
            } else if (m_num > 0 && m_den < 0) {
                m_num = -m_num;
            }
            m_den = std::abs(m_den);
        }

        void reduce() {
            int div{2};
            if (std::abs(m_num) == m_den && (m_den != 0 || m_num != 0)) {
                m_num /= m_den;
                m_den /= m_den;
            } else {
                do {
                    if (m_num % div == 0 && m_den % div == 0) {
                        m_num /= div;
                        m_den /= div;
                    } else {
                        ++div;
                    }
                } while (div <= std::abs(m_num) / 2 || div <= std::abs(m_den) / 2);
            }
        }
        /*
         * A helper function for round method
         */
        void round_floor() {
            while (m_num % m_den != 0) {
                (is_positive()) ? --m_num : ++m_num;
            }
            reduce();
        }
        /*
         * A helper function for round method
         */
        void round_ceil() {
            while (m_num % m_den != 0) {
                (is_positive()) ? ++m_num : --m_num;
            }
            reduce();
        }
    };


    inline ratio_d_t operator+(ratio_d_t rt1, const ratio_d_t& rt2) {
        rt1 += rt2;
        return rt1;
    }

    inline ratio_d_t operator+(ratio_d_t rt, int n) {
        rt += n;
        return rt;
    }

    inline ratio_d_t operator+(int n, ratio_d_t rt) {
        rt += n;
        return rt;
    }

    inline ratio_d_t operator-(ratio_d_t rt1, const ratio_d_t& rt2) {
        rt1 -= rt2;
        return rt1;
    }

    inline ratio_d_t operator-(ratio_d_t rt, int n) {
        rt -= n;
        return rt;
    }

    inline ratio_d_t operator-(int n, ratio_d_t rt) {
        auto res = ratio_d_t{n, 1} - rt;
        return res;
    }

    inline ratio_d_t operator*(ratio_d_t rt1, const ratio_d_t& rt2) {
        rt1 *= rt2;
        return rt1;
    }

    inline ratio_d_t operator*(ratio_d_t rt, int n) {
        rt *= n;
        return rt;
    }

    inline ratio_d_t operator*(int n, ratio_d_t rt) {
        rt *= n;
        return rt;
    }

    inline ratio_d_t operator/(ratio_d_t rt1, const ratio_d_t& rt2) {
        rt1 /= rt2;
        return rt1;
    }

    inline ratio_d_t operator/(ratio_d_t rt, int n) {
        rt /= n;
        return rt;
    }

    inline ratio_d_t operator/(int n, ratio_d_t rt) {
        rt.inverse_base();
        rt *= n;
        return rt;
    }

    inline std::ostream& operator<<(std::ostream& os, const ratio_d_t& rt) {
        os << rt.get_string();
        return os;
    }
    /*
     * The input HAS TO BE in format num/den! No spaces and other characters
     * If no denominator => den = 1
     * If no / => den = 1
     * If no nUminator => the ratio = 1/1
     */
    inline std::istream& operator>>(std::istream& is, ratio_d_t& rt) {
        // Reset the ratio
        rt.reset();
        int num, den;
        char div_sign{};
        if (is >> num) {
            rt.set_num(num);
            if (is.peek() == '/') {
                is >> div_sign;
                if (is >> den) {
                    rt.set_den(den);
                } else {
                    rt.set_den(1);
                }
            } else {
                rt.set_den(1);
            }
        }
        return is;
    }
    // These are the declarations of all the math functions
    ratio_d_t pow(const ratio_d_t& rt, int n);
    ratio_d_t ceil(const ratio_d_t& rt);
    ratio_d_t floor(const ratio_d_t& rt);
    ratio_d_t trunc(const ratio_d_t& rt);
    ratio_d_t round(const ratio_d_t& rt);
    ratio_d_t min(const ratio_d_t& rt1, const ratio_d_t& rt2);
    ratio_d_t max(const ratio_d_t& rt1, const ratio_d_t& rt2);
    ratio_d_t abs(const ratio_d_t& rt);
}

#endif //TEMPLATE_RATIOD_T_HPP
