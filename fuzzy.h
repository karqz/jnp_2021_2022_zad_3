<<<<<<< HEAD
#ifndef FUZZY_H
#define FUZZY_H

#include <vector>
#include <iostream>
#include <tuple>
=======
#ifndef __FUZZY__
#define __FUZZY__
>>>>>>> 52658674e21442069065c2d3ed4cc9997eb7864b

using real_t = double;
using fuzzy_rank_t = std::tuple<real_t, real_t, real_t>;
using std::strong_ordering;

constinit crisp_zero = TriFuzzyNum(0,0,0);

consteval TriFuzzyNum crisp_number(real_t v) {
    return TriFuzzyNum(v, v, v);
}

class TriFuzzyNum {
    real_t l;
    real_t m;
    real_t u;
<<<<<<< HEAD

    friend std::ostream& operator<<(std::ostream& os, const TriFuzzyNum& num) {
        os << "(" << num.l
           << ", " << num.m
           << ", " << num.u << ")";

        return os;
    }
public:

    constexpr TriFuzzyNum(const real_t &a, const real_t &b, const real_t &c) {
        real_t nums[] = {a, b, c};
        std::sort(std::begin(nums), std::end(nums));

        l = nums[0];
        m = nums[1];
        u = nums[2];
    }

    //konstruktor kopiujacy
    TriFuzzyNum(TriFuzzyNum& that) {
        l = that.l;
        m = that.m;
        u = that.u;
    }
    //konstruktor przenoszacy
    TriFuzzyNum(TriFuzzyNum&& that) {
        l = move(that.l);
        m = move(that.m);
        u = move(that.u);
    }

    constexpr real_t lower_value() { return l; }

    constexpr real_t modal_value() { return m; }

    constexpr real_t upper_value() { return u; }

    //operator kopiujacy
    TriFuzzyNum& operator=(const TriFuzzyNum& that) {
        l = that.l;
        m = that.m;
        u = that.u;
        return *this;
    }
    //operator przenoszacy
    TriFuzzyNum& operator=(TriFuzzyNum&& that) {
        l = move(that.l);
        m = move(that.m);
        u = move(that.u);
        return *this;
    }

    TriFuzzyNum& operator+=(const TriFuzzyNum& that);
    TriFuzzyNum& operator-=(const TriFuzzyNum& that);
    TriFuzzyNum& operator*=(const TriFuzzyNum& that);

    const TriFuzzyNum operator+(const TriFuzzyNum &that) const {
        real_t l2 = that.l, m2 = that.m, u2 = that.u;
        return TriFuzzyNum(l + l2, m + m2, u + u2);
    }

    const TriFuzzyNum operator-(const TriFuzzyNum &that) const {
        real_t l2 = that.l, m2 = that.m, u2 = that.u;
        return TriFuzzyNum(l - u2, m - m2, u - l2);
    }

    const TriFuzzyNum operator*(const TriFuzzyNum &that) const {
        real_t l2 = that.l, m2 = that.m, u2 = that.u;
        return TriFuzzyNum(l * l2, m * m2, u * u2);
    }

    fuzzy_rank_t getRank() const {
        real_t z = (u - l) + sqrt(1 + (u - m) * (u - m)) + sqrt(1 + (m - l) * (m - l));
        real_t x = ((u - l) * m + sqrt(1 + (u - m) * (u - m)) * l + sqrt(1 + (m - l) * (m - l)) * u) / z;
        real_t y = (u - l) / z;

        return std::make_tuple(x - y / 2, 1 - y, m);
    }

    auto operator<=>(const int& a) const;
    auto operator<=>(const TriFuzzyNum& that) const {
        fuzzy_rank_t rank1 = getRank();
        fuzzy_rank_t rank2 = that.getRank();

        real_t first_1 = get<0>(rank1), second_1 = get<1>(rank1), third_1 = get<2>(rank1);
        real_t first_2 = get<0>(rank2), second_2 = get<1>(rank2), third_2 = get<2>(rank2);

        if (first_1 > first_2) return strong_ordering::greater;
        else if (first_2 > first_1) return strong_ordering::less;
        else {
            if (second_1 > second_2) return strong_ordering::greater;
            else if (second_2 > second_1) return strong_ordering::less;
            else {
                if (third_1 > third_1) return strong_ordering::greater;
                else if (third_2 > third_1) return strong_ordering::less;
                else return strong_ordering::equal;
            }
        }
    }
};
=======
    public:
        

        constexpr TriFuzzyNum(const real_t &a, const real_t &b, const real_t &c) {
            l = a;
            m = b;
            u = c;
        };


        TriFuzzyNum& operator=(const TriFuzzyNum& that);

        TriFuzzyNum& operator+=(const TriFuzzyNum& that);
        TriFuzzyNum& operator-=(const TriFuzzyNum& that);
        TriFuzzyNum& operator*=(const TriFuzzyNum& that);

        const TriFuzzyNum operator+(const TriFuzzyNum &that) const;
        const TriFuzzyNum operator-(const TriFuzzyNum &that) const;
        const TriFuzzyNum operator*(const TriFuzzyNum &that) const;

        
        auto operator<=>(const int& a) const; 
        auto operator<=>(const TriFuzzyNum& a) const = default;

    friend std::ostream& operator<<(std::ostream&, const TriFuzzyNum&);
};

>>>>>>> 52658674e21442069065c2d3ed4cc9997eb7864b

#endif //__FUZZY__
