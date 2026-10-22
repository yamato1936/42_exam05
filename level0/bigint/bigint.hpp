#ifndef BIGINT_HPP
#define BIGINT_HPP
#include <iostream>
#include <string>

class bigint {
    std::string digits_;
    int compare(const bigint &other) const;
public:
    bigint(unsigned long value = 0);
    bigint(const bigint &other);
    bigint &operator=(const bigint &other);
    ~bigint();

    const std::string &str() const;
    bigint &operator+=(const bigint &other);
    bigint operator+(const bigint &other) const;
    bigint &operator++();
    bigint operator++(int);

    bigint &operator<<=(unsigned long amount);
    bigint &operator>>=(unsigned long amount);
    bigint &operator<<=(const bigint &amount);
    bigint &operator>>=(const bigint &amount);
    bigint operator<<(unsigned long amount) const;
    bigint operator>>(unsigned long amount) const;
    bigint operator<<(const bigint &amount) const;
    bigint operator>>(const bigint &amount) const;

    bool operator==(const bigint &other) const;
    bool operator!=(const bigint &other) const;
    bool operator<(const bigint &other) const;
    bool operator<=(const bigint &other) const;
    bool operator>(const bigint &other) const;
    bool operator>=(const bigint &other) const;
};

std::ostream &operator<<(std::ostream &out, const bigint &value);
#endif
