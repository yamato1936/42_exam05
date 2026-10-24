#include "bigint.hpp"

std::ostream& operator<<(std::ostream& os, const bigint& b) {
    return os << b.str();
}
