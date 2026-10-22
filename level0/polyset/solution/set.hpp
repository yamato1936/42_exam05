#pragma once
#include "../given/searchable_bag.hpp"
// Non-owning wrapper: the underlying bag must outlive this set.
class set {
    searchable_bag *b;
public:
    explicit set(searchable_bag& x);
    set(const set& x);
    set& operator=(const set& x);
    ~set();
    bool has(int n) const;
    void insert(int n);
    void insert(int *v, int n);
    void print() const;
    void clear();
    searchable_bag& get_bag();
    const searchable_bag& get_bag() const;
};
