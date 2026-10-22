#include "../bigint.hpp"
#include <cassert>
#include <sstream>

static std::string show(const bigint &v) {
    std::ostringstream os;
    os << v;
    return os.str();
}

int main() {
    const bigint a(42);
    bigint b(21), c, d(1337), e(d);
    assert(a + b == bigint(63));
    assert((c += a) == a);
    assert(++b == bigint(22));
    assert(b++ == bigint(22));
    assert(b == bigint(23));
    assert(show((b << 10) + 42) == "230000000042");
    assert(show(d <<= 4) == "13370000");
    assert(show(d >>= bigint(2)) == "133700");
    assert(d > a && d >= a && a < d && a <= d);
    assert(a != d && e == bigint(1337));
    bigint huge(1);
    for (int i = 0; i < 100; ++i) huge += huge;
    assert(show(huge).size() == 31);
    assert(show(bigint(0) << 200) == "0");
    assert(show(bigint(123) >> bigint(20)) == "0");
    assert(show(bigint(123) << bigint(2)) == "12300");
    assert(show(bigint(1000) >> bigint(3)) == "1");
    assert(show(bigint(0) + bigint(0)) == "0");
}
