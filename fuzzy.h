#ifndef FUZZY_H
#define FUZZY_H

#include <vector>

using real_t = double;

class TriFuzzyNum {
    real_t l, m, u;
public:
    TriFuzzyNum(real_t, real_t, real_t);
};

TriFuzzyNum::TriFuzzyNum (real_t a, real_t b, real_t c) {
    std::vector<real_t> nums = {a, b, c};
    sort(nums.begin(), nums.end());
    l = nums[0];
    m = nums[1];
    u = nums[2];
}

#endif //FUZZY_H
