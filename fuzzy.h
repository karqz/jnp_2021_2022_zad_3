#ifndef __FUZZY__
#define __FUZZY__

using real_t = double;

class TriFuzzyNum {
    real_t l;
    real_t m;
    real_t u;
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


#endif //__FUZZY__
