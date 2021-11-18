#ifndef __FUZZY__
#define __FUZZY__

#include<iostream>
#include<set>
#include<tuple>
#include<math.h>

using real_t = double;
using fuzzy_rank_t = std::tuple<real_t, real_t, real_t>;
using namespace std;



class TriFuzzyNum {
    
    public:

        constexpr TriFuzzyNum(const real_t &a, const real_t &b, const real_t &c) {
            real_t nums[] = {a, b, c};
            sort(begin(nums), end(nums));

            l = nums[0];
            m = nums[1];
            u = nums[2];
        }

        //konstruktor kopiujacy
        TriFuzzyNum(const TriFuzzyNum& that):l(that.l),m(that.m),u(that.u) {}
        
        //konstruktor przenoszacy
        TriFuzzyNum(TriFuzzyNum&& that):l(move(that.l)),m(move(that.m)),u(move(that.u)) {}

        constexpr real_t lower_value() const { return l; }

        constexpr real_t modal_value() const { return m; }

        constexpr real_t upper_value() const { return u; }

        //operator kopiujacy
        TriFuzzyNum& operator=(const TriFuzzyNum& that) {
            if (this != &that) {
                l = that.l;
                m = that.m;
                u = that.u;
            }
            return *this;
        }

        //operator przenoszacy
        TriFuzzyNum& operator=(TriFuzzyNum&& that) {
            l = move(that.l);
            m = move(that.m);
            u = move(that.u);
            return *this;
        }

        TriFuzzyNum& operator+=(const TriFuzzyNum& that) {
            l += that.l;
            m += that.m;
            u += that.u;
            return *this;
        }

        TriFuzzyNum& operator-=(const TriFuzzyNum& that) {
            l -= that.u;
            m -= that.m;
            u -= that.l;
            return *this;
        }

        TriFuzzyNum& operator*=(const TriFuzzyNum& that) {
            l *= that.l;
            m *= that.m;
            u *= that.u;
            return *this;
        }

        const TriFuzzyNum operator+(const TriFuzzyNum& that) const {
            TriFuzzyNum result = *this;
            result += that;
            return result;
        }

        const TriFuzzyNum operator-(const TriFuzzyNum& that) const {
            TriFuzzyNum result = *this;
            result -= that;
            return result;
        }

        const TriFuzzyNum operator*(const TriFuzzyNum& that) const {
            TriFuzzyNum result = *this;
            result *= that;
            return result;
        }

        constexpr fuzzy_rank_t getRank() const {
            real_t z = (u - l) + sqrt(1 + (u - m) * (u - m)) + sqrt(1 + (m - l) * (m - l));
            real_t x = ((u - l) * m + sqrt(1 + (u - m) * (u - m)) * l + sqrt(1 + (m - l) * (m - l)) * u) / z;
            real_t y = (u - l) / z;

            return make_tuple(x - y / 2, 1 - y, m);
        }

        constexpr bool operator==(const TriFuzzyNum& that) const {
            return l == that.l && m == that.m && u == that.u;
        }

        constexpr bool operator!=(const TriFuzzyNum& that) const {
            return !(*this == that);
        }

        auto operator<=>(const int& a) const;
        constexpr auto operator<=>(const TriFuzzyNum& that) const {
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

        friend std::ostream& operator<<(std::ostream& os, const TriFuzzyNum& num) {
            os << "("  << num.l
               << ", " << num.m
               << ", " << num.u << ")";

            return os;
        }

    private:
        real_t l, m, u;
};

constinit TriFuzzyNum crisp_zero = TriFuzzyNum(0, 0, 0);

consteval TriFuzzyNum crisp_number(real_t v) {
    return TriFuzzyNum(v, v, v);
}

class TriFuzzyNumSet {
    public:
        TriFuzzyNumSet(initializer_list<TriFuzzyNum> args) {
            set = multiset<TriFuzzyNum>(args.begin(), args.end());
        }

        TriFuzzyNumSet(const TriFuzzyNumSet& that):set(that.set) {}

        TriFuzzyNumSet(TriFuzzyNumSet&& that):set(move(that.set)) {}

        TriFuzzyNumSet& operator=(const TriFuzzyNumSet& that) {
            if (this != &that) {
                set = that.set;
            }
            return *this;
        }

        TriFuzzyNumSet& operator=(TriFuzzyNumSet&& that) {
            set = move(that.set);
            return *this;
        }

        ~TriFuzzyNumSet() {}

        void insert(const TriFuzzyNum& number) {
            set.insert(number);
        }

        void insert(TriFuzzyNum&& number) {
            set.insert(move(number));
        }

        void remove(const TriFuzzyNum& number) {
            set.erase(number);
        }

        void remove(TriFuzzyNum&& number) {
            set.erase(move(number));
        }

        TriFuzzyNum arithmetic_mean() {
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
