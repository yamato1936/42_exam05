#include "searchable_array_bag.hpp"
searchable_array_bag::searchable_array_bag() {}
searchable_array_bag::searchable_array_bag(const searchable_array_bag& b) : array_bag(b) {}
searchable_array_bag& searchable_array_bag::operator=(const searchable_array_bag& b) {
    if (this != &b) array_bag::operator=(b);
    return *this;
}
searchable_array_bag::~searchable_array_bag() {}
bool searchable_array_bag::has(int n) const {
    for (int i = 0; i < size; ++i)
        if (data[i] == n) return true;
    return false;
}
