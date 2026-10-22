#pragma once
#include "../given/searchable_bag.hpp"

// Non-owning wrapper: the referenced bag must outlive the set.
// Start with an empty searchable_bag to guarantee uniqueness throughout.
class set : public bag {
    searchable_bag *_bag;
public:
    explicit set(searchable_bag &underlying);
    set(const set &other);
    set &operator=(const set &other);
    ~set();

    void insert(int value);
    void insert(int *values, int count);
    bool has(int value) const;
    void print() const;
    void clear();
    searchable_bag &get_bag();
    const searchable_bag &get_bag() const;
};
