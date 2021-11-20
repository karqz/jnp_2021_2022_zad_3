#ifndef __FUZZY__
#define __FUZZY__

#include<iostream>
#include<set>
#include<tuple>
#include<cmath>
#include<algorithm>

using real_t = double;
using fuzzy_rank_t = std::tuple<real_t, real_t, real_t>;
using namespace std;

class TriFuzzyNum {
    
    public:

        constexpr TriFuzzyNum(const real_t &a, const real_t &b, const real_t &c) {
            l = a;
            m = b;
            u = c;
            sortAndUpdateFuzzyValues();
        }

        TriFuzzyNum(const TriFuzzyNum& that) = default;

        TriFuzzyNum(TriFuzzyNum&& that) = default;

        ~TriFuzzyNum() = default;

        [[nodiscard]] constexpr real_t lower_value() const { return l; }

        [[nodiscard]] constexpr real_t modal_value() const { return m; }

        [[nodiscard]] constexpr real_t upper_value() const { return u; }

        TriFuzzyNum& operator=(const TriFuzzyNum& that) = default;

        constexpr TriFuzzyNum& operator=(TriFuzzyNum&& that) = default;

        constexpr TriFuzzyNum& operator+=(const TriFuzzyNum& that) {
            l += that.l;
            m += that.m;
            u += that.u;
            return *this;
        }

        constexpr TriFuzzyNum& operator-=(const TriFuzzyNum& that) {
            l -= that.u;
            m -= that.m;
            u -= that.l;
            return *this;
        }

        constexpr TriFuzzyNum& operator*=(const TriFuzzyNum& that) {
            l *= that.l;
            m *= that.m;
            u *= that.u;
            sortAndUpdateFuzzyValues();
            return *this;
        }

        constexpr TriFuzzyNum operator+(const TriFuzzyNum& that) const {
            TriFuzzyNum result = *this;
            result += that;
            return result;
        }

        constexpr TriFuzzyNum operator-(const TriFuzzyNum& that) const {
            TriFuzzyNum result = *this;
            result -= that;
            return result;
        }

        constexpr TriFuzzyNum operator*(const TriFuzzyNum& that) const {
            TriFuzzyNum result = *this;
            result *= that;
            return result;
        }

        constexpr bool operator==(const TriFuzzyNum& that) const {
            return l == that.l && m == that.m && u == that.u;
        }

        constexpr bool operator!=(const TriFuzzyNum& that) const {
            return !(*this == that);
        }

        constexpr auto operator<=>(const TriFuzzyNum& that) const {
            fuzzy_rank_t rank1 = getRank();
            fuzzy_rank_t rank2 = that.getRank();

            return rank1 <=> rank2;
        }

        friend std::ostream& operator<<(std::ostream& os, const TriFuzzyNum& num) {
            os << "("  << num.l
               << ", " << num.m
               << ", " << num.u << ")";

            return os;
        }

    private:
        real_t l, m, u;

        [[nodiscard]] constexpr fuzzy_rank_t getRank() const {
            real_t z = (u - l) + sqrt(1 + (u - m) * (u - m)) + sqrt(1 + (m - l) * (m - l));
            real_t x = ((u - l) * m + sqrt(1 + (u - m) * (u - m)) * l + sqrt(1 + (m - l) * (m - l)) * u) / z;
            real_t y = (u - l) / z;

            return make_tuple(x - y / 2, 1 - y, m);
        }

        constexpr void sortAndUpdateFuzzyValues() {
            std::array<real_t, 3> nums = {l, m, u};
            std::ranges::sort(nums);

            l = nums[0];
            m = nums[1];
            u = nums[2];
        }
};

consteval TriFuzzyNum crisp_number(real_t v) {
    return {v, v, v};
}

inline constinit const TriFuzzyNum crisp_zero = crisp_number(0);

class TriFuzzyNumSet {
    public:
        TriFuzzyNumSet():set(multiset<TriFuzzyNum>()) {}

        TriFuzzyNumSet(initializer_list<TriFuzzyNum> args):set(args) {}

        TriFuzzyNumSet(const TriFuzzyNumSet& that) = default;

        TriFuzzyNumSet(TriFuzzyNumSet&& that) = default;

        TriFuzzyNumSet& operator=(const TriFuzzyNumSet& that) = default;

        TriFuzzyNumSet& operator=(TriFuzzyNumSet&& that) = default;

        ~TriFuzzyNumSet() = default;

        void insert(const TriFuzzyNum& number) {
            set.insert(number);
        }

        void insert(TriFuzzyNum&& number) {
            set.insert(move(number));
        }

        void remove(const TriFuzzyNum& number) {
            set.erase(number);
        }

        TriFuzzyNum arithmetic_mean() {
            if (set.empty()) {
                throw std::length_error("TriFuzzyNumSet::arithmetic_mean - the set is empty.");
            }

            TriFuzzyNum result = crisp_zero;
            real_t size = 0;
            for (TriFuzzyNum number : set) {
                result += number;
                size++;
            }

            result *= TriFuzzyNum(1/size, 1/size, 1/size);

            return result;
        }

    private:
        multiset<TriFuzzyNum> set;
};

#endif //__FUZZY__
