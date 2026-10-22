#include "../vect2.hpp"
#include <cassert>
#include <sstream>

int main()
{
    vect2 a(5, 2), b(1, 7);
    assert(a - b == vect2(4, -5));
    assert((a -= b) == vect2(4, -5));
    assert((--a) == vect2(3, -6));
    assert((a++) == vect2(3, -6));
    assert(a == vect2(4, -5));
    assert((2 * b) == vect2(2, 14));
    const vect2 c(7, 8);
    assert(c[0] == 7 && c[1] == 8);
    std::ostringstream out;
    out << c;
    assert(out.str() == "{7, 8}");
}
