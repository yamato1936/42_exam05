#ifndef VECT2_HPP
#define VECT2_HPP
#include <iostream>

class vect2
{
    int x, y;
public:
    vect2(int a = 0, int b = 0) : x(a), y(b) {}
    int& operator[](int i) { return i ? y : x; }
    int operator[](int i) const { return i ? y : x; }

    vect2& operator+=(const vect2& v) { x += v.x; y += v.y; return *this; }
    vect2& operator-=(const vect2& v) { x -= v.x; y -= v.y; return *this; }
    vect2& operator*=(int n) { x *= n; y *= n; return *this; }

    vect2 operator+(const vect2& v) const { vect2 t(*this); return t += v; }
    vect2 operator-(const vect2& v) const { vect2 t(*this); return t -= v; }
    vect2 operator*(int n) const { vect2 t(*this); return t *= n; }
    vect2 operator-() const { return vect2(-x, -y); }

    vect2& operator++() { return *this += vect2(1, 1); }
    vect2 operator++(int) { vect2 t(*this); ++(*this); return t; }
    vect2& operator--() { return *this -= vect2(1, 1); }
    vect2 operator--(int) { vect2 t(*this); --(*this); return t; }

    bool operator==(const vect2& v) const { return x == v.x && y == v.y; }
    bool operator!=(const vect2& v) const { return !(*this == v); }
};
vect2 operator*(int n, const vect2& v);
std::ostream& operator<<(std::ostream& os, const vect2& v);
#endif
