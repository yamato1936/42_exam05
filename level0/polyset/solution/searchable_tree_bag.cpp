#include "searchable_tree_bag.hpp"
searchable_tree_bag::searchable_tree_bag() {}
searchable_tree_bag::searchable_tree_bag(const searchable_tree_bag& b) : tree_bag(b) {}
searchable_tree_bag& searchable_tree_bag::operator=(const searchable_tree_bag& b) {
    if (this != &b) tree_bag::operator=(b);
    return *this;
}
searchable_tree_bag::~searchable_tree_bag() {}
bool searchable_tree_bag::has(int n) const {
    const node *p = tree;
    while (p && p->value != n)
        p = n < p->value ? p->l : p->r;
    return p != 0;
}
