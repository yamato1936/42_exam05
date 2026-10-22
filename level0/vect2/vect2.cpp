#include "vect2.hpp"

vect2 operator*(int n, const vect2& v) { return v * n; }
std::ostream& operator<<(std::ostream& os, const vect2& v)
{
    return os << "{" << v[0] << ", " << v[1] << "}";
}
