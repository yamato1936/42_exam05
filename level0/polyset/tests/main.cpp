#include "../solution/searchable_array_bag.hpp"
#include "../solution/searchable_tree_bag.hpp"
#include "../solution/set.hpp"
#include <cassert>

int main() {
    searchable_array_bag a;
    searchable_tree_bag t;
    set sa(a), st(t);
    int values[] = {4, 2, 4, 9, 2, 1};
    sa.insert(values, 6);
    st.insert(values, 6);
    assert(a.has(4) && a.has(1) && !a.has(8));
    assert(t.has(9) && t.has(2) && !t.has(8));
    assert(sa.get_bag().has(4));
    assert(st.get_bag().has(9));
    const searchable_array_bag copied(a);
    assert(copied.has(1));
    a.clear();
    assert(!a.has(1) && copied.has(1));
    const searchable_tree_bag copy_tree(t);
    t.clear();
    assert(!t.has(2) && copy_tree.has(2));
    int second[] = {5, 5};
    sa.insert(second, 2);
    st.insert(second, 2);
    assert(a.has(5) && t.has(5));
    return 0;
}
