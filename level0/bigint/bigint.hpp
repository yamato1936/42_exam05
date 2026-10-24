#ifndef BIGINT_HPP
#define BIGINT_HPP
#include <iostream>
#include <string>
#include <algorithm>
#include <stdexcept>

class bigint {
    std::string s;

    size_t value() const {
        size_t n = 0;
        for (size_t i = 0; i < s.size(); ++i)
            n = n * 10 + s[i] - '0';
        return n;
    }

public:
    bigint(unsigned long n = 0) {
        do { s.insert(s.begin(), char('0' + n % 10)); n /= 10; } while (n);
    }

    bigint& operator+=(const bigint& b) {
        size_t i = s.size(), j = b.s.size();
        int carry = 0;
        std::string r;
        while (i || j || carry) {
            int d = carry;
            if (i) d += s[--i] - '0';
            if (j) d += b.s[--j] - '0';
            r += char('0' + d % 10);
            carry = d / 10;
        }
        std::reverse(r.begin(), r.end());
        s = r;
        return *this;
    }
    bigint operator+(const bigint& b) const { bigint t(*this); return t += b; }
    bigint& operator++() { return *this += 1; }
    bigint operator++(int) { bigint t(*this); ++*this; return t; }

    bool operator==(const bigint& b) const { return s == b.s; }
    bool operator!=(const bigint& b) const { return !(*this == b); }
    bool operator<(const bigint& b) const {
        return s.size() == b.s.size() ? s < b.s : s.size() < b.s.size();
    }
    bool operator<=(const bigint& b) const { return !(b < *this); }
    bool operator>(const bigint& b) const { return b < *this; }
    bool operator>=(const bigint& b) const { return !(*this < b); }

    bigint& operator<<=(const bigint& b) {
        if (s != "0") {
            if (b > bigint(s.max_size() - s.size()))
                throw std::length_error("shift too large");
            s.append(b.value(), '0');
        }
        return *this;
    }
    bigint& operator>>=(const bigint& b) {
        if (b >= bigint(s.size())) s = "0";
        else s.erase(s.size() - b.value());
        return *this;
    }
    bigint operator<<(const bigint& b) const { bigint t(*this); return t <<= b; }
    bigint operator>>(const bigint& b) const { bigint t(*this); return t >>= b; }

    const std::string& str() const { return s; }
};
std::ostream& operator<<(std::ostream& os, const bigint& b);
#endif
