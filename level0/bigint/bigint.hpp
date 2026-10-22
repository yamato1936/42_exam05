#ifndef BIGINT_HPP
#define BIGINT_HPP
#include <iostream>
#include <string>

class bigint {
    std::string s;
    int cmp(const bigint& b) const;
public:
    bigint(unsigned long n = 0);
    bigint(const bigint& b);
    bigint& operator=(const bigint& b);
    ~bigint();
    bigint& operator+=(const bigint& b);
    bigint operator+(const bigint& b) const;
    bigint& operator++();
    bigint operator++(int);
    bigint& operator<<=(unsigned long n);
    bigint& operator>>=(unsigned long n);
    bigint& operator<<=(const bigint& n);
    bigint& operator>>=(const bigint& n);
    bigint operator<<(unsigned long n) const;
    bigint operator>>(unsigned long n) const;
    bigint operator<<(const bigint& n) const;
    bigint operator>>(const bigint& n) const;
    bool operator==(const bigint& b) const;
    bool operator!=(const bigint& b) const;
    bool operator<(const bigint& b) const;
    bool operator<=(const bigint& b) const;
    bool operator>(const bigint& b) const;
    bool operator>=(const bigint& b) const;
    const std::string& str() const;
};
std::ostream& operator<<(std::ostream& o, const bigint& b);
#endif
