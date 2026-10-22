#include "set.hpp"
set::set(searchable_bag& x) : b(&x) {}
set::set(const set& x) : b(x.b) {}
set& set::operator=(const set& x) { if (this != &x) b = x.b; return *this; }
set::~set() {}
bool set::has(int n) const { return b->has(n); }
void set::insert(int n) { if (!has(n)) b->insert(n); }
void set::insert(int *v, int n) {
    for (int i = 0; i < n; ++i) insert(v[i]);
}
void set::print() const { b->print(); }
void set::clear() { b->clear(); }
searchable_bag& set::get_bag() { return *b; }
const searchable_bag& set::get_bag() const { return *b; }
