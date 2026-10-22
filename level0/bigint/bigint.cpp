#include "bigint.hpp"
#include <limits>
#include <stdexcept>

bigint::bigint(unsigned long value) : digits_("0") {
    if (!value)
        return;
    digits_.clear();
    while (value) {
        digits_.insert(digits_.begin(), static_cast<char>('0' + value % 10));
        value /= 10;
    }
}
bigint::bigint(const bigint &other) : digits_(other.digits_) {}
bigint &bigint::operator=(const bigint &other) {
    if (this != &other)
        digits_ = other.digits_;
    return *this;
}
bigint::~bigint() {}
const std::string &bigint::str() const { return digits_; }

int bigint::compare(const bigint &other) const {
    if (digits_.size() < other.digits_.size()) return -1;
    if (digits_.size() > other.digits_.size()) return 1;
    if (digits_ < other.digits_) return -1;
    if (digits_ > other.digits_) return 1;
    return 0;
}

bigint &bigint::operator+=(const bigint &other) {
    std::string result;
    size_t i = digits_.size(), j = other.digits_.size();
    int carry = 0;
    while (i || j || carry) {
        int d = carry;
        if (i) d += digits_[--i] - '0';
        if (j) d += other.digits_[--j] - '0';
        result.insert(result.begin(), static_cast<char>('0' + d % 10));
        carry = d / 10;
    }
    digits_.swap(result);
    return *this;
}
bigint bigint::operator+(const bigint &other) const {
    bigint result(*this);
    result += other;
    return result;
}
bigint &bigint::operator++() { return *this += bigint(1); }
bigint bigint::operator++(int) { bigint old(*this); ++(*this); return old; }

bigint &bigint::operator<<=(unsigned long amount) {
    if (digits_ != "0") {
        if (amount > digits_.max_size() - digits_.size())
            throw std::length_error("digitshift too large");
        digits_.append(static_cast<size_t>(amount), '0');
    }
    return *this;
}
bigint &bigint::operator>>=(unsigned long amount) {
    if (amount >= digits_.size())
        digits_ = "0";
    else
        digits_.erase(digits_.size() - static_cast<size_t>(amount));
    return *this;
}
bigint &bigint::operator<<=(const bigint &amount) {
    size_t n = 0;
    const size_t max = std::numeric_limits<size_t>::max();
    for (size_t i = 0; i < amount.digits_.size(); ++i) {
        const size_t d = static_cast<size_t>(amount.digits_[i] - '0');
        if (n > (max - d) / 10)
            throw std::length_error("digitshift too large");
        n = n * 10 + d;
    }
    if (n > digits_.max_size() - digits_.size() && digits_ != "0")
        throw std::length_error("digitshift too large");
    if (digits_ != "0")
        digits_.append(n, '0');
    return *this;
}
bigint &bigint::operator>>=(const bigint &amount) {
    size_t n = 0;
    const size_t max = std::numeric_limits<size_t>::max();
    for (size_t i = 0; i < amount.digits_.size(); ++i) {
        const size_t d = static_cast<size_t>(amount.digits_[i] - '0');
        if (n > (max - d) / 10) {
            digits_ = "0";
            return *this;
        }
        n = n * 10 + d;
        if (n >= digits_.size()) {
            digits_ = "0";
            return *this;
        }
    }
    digits_.erase(digits_.size() - n);
    return *this;
}
bigint bigint::operator<<(unsigned long n) const { bigint b(*this); b <<= n; return b; }
bigint bigint::operator>>(unsigned long n) const { bigint b(*this); b >>= n; return b; }
bigint bigint::operator<<(const bigint &n) const { bigint b(*this); b <<= n; return b; }
bigint bigint::operator>>(const bigint &n) const { bigint b(*this); b >>= n; return b; }

bool bigint::operator==(const bigint &v) const { return compare(v) == 0; }
bool bigint::operator!=(const bigint &v) const { return compare(v) != 0; }
bool bigint::operator<(const bigint &v) const { return compare(v) < 0; }
bool bigint::operator<=(const bigint &v) const { return compare(v) <= 0; }
bool bigint::operator>(const bigint &v) const { return compare(v) > 0; }
bool bigint::operator>=(const bigint &v) const { return compare(v) >= 0; }
std::ostream &operator<<(std::ostream &out, const bigint &v) {
    return out << v.str();
}
