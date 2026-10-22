#include "bigint.hpp"
#include <stdexcept>

bigint::bigint(unsigned long n) {
    do { s.insert(s.begin(), '0' + n % 10); n /= 10; } while (n);
}
bigint::bigint(const bigint& b) : s(b.s) {}
bigint& bigint::operator=(const bigint& b) { if (this != &b) s = b.s; return *this; }
bigint::~bigint() {}

int bigint::cmp(const bigint& b) const {
    if (s.size() != b.s.size()) return s.size() < b.s.size() ? -1 : 1;
    return s == b.s ? 0 : (s < b.s ? -1 : 1);
}
bigint& bigint::operator+=(const bigint& b) {
    std::string r;
    size_t i = s.size(), j = b.s.size();
    int carry = 0;
    while (i || j || carry) {
        int d = carry;
        if (i) d += s[--i] - '0';
        if (j) d += b.s[--j] - '0';
        r.insert(r.begin(), '0' + d % 10);
        carry = d / 10;
    }
    s = r;
    return *this;
}
bigint bigint::operator+(const bigint& b) const { bigint a(*this); return a += b; }
bigint& bigint::operator++() { return *this += bigint(1); }
bigint bigint::operator++(int) { bigint a(*this); ++*this; return a; }

bigint& bigint::operator<<=(unsigned long n) {
    if (s != "0") {
        if (n > s.max_size() - s.size()) throw std::length_error("shift too large");
        s.append((size_t)n, '0');
    }
    return *this;
}
bigint& bigint::operator>>=(unsigned long n) {
    if (n >= s.size()) s = "0";
    else s.erase(s.size() - (size_t)n);
    return *this;
}
bigint& bigint::operator<<=(const bigint& n) {
    if (s == "0") return *this;
    if (n > bigint(s.max_size() - s.size())) throw std::length_error("shift too large");
    unsigned long k = 0;
    for (size_t i = 0; i < n.s.size(); ++i) k = k * 10 + n.s[i] - '0';
    return *this <<= k;
}
bigint& bigint::operator>>=(const bigint& n) {
    if (n >= bigint(s.size())) { s = "0"; return *this; }
    unsigned long k = 0;
    for (size_t i = 0; i < n.s.size(); ++i) k = k * 10 + n.s[i] - '0';
    return *this >>= k;
}
bigint bigint::operator<<(unsigned long n) const { bigint a(*this); return a <<= n; }
bigint bigint::operator>>(unsigned long n) const { bigint a(*this); return a >>= n; }
bigint bigint::operator<<(const bigint& n) const { bigint a(*this); return a <<= n; }
bigint bigint::operator>>(const bigint& n) const { bigint a(*this); return a >>= n; }
bool bigint::operator==(const bigint& b) const { return cmp(b) == 0; }
bool bigint::operator!=(const bigint& b) const { return cmp(b) != 0; }
bool bigint::operator<(const bigint& b) const { return cmp(b) < 0; }
bool bigint::operator<=(const bigint& b) const { return cmp(b) <= 0; }
bool bigint::operator>(const bigint& b) const { return cmp(b) > 0; }
bool bigint::operator>=(const bigint& b) const { return cmp(b) >= 0; }
const std::string& bigint::str() const { return s; }
std::ostream& operator<<(std::ostream& o, const bigint& b) { return o << b.str(); }
