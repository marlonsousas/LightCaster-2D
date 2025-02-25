#ifndef VEC2_HPP
#define VEC2_HPP

#include <cmath>

struct Vec2 {
    float x, y;

    Vec2(float x = 0, float y = 0) : x(x), y(y) {}

    Vec2 operator+(const Vec2& v) const { return Vec2(x + v.x, y + v.y); }
    Vec2 operator-(const Vec2& v) const { return Vec2(x - v.x, y - v.y); }
    Vec2 operator*(float f) const { return Vec2(x * f, y * f); }

    float dot(const Vec2& v) const { return x * v.x + y * v.y; }
    float cross(const Vec2& v) const { return x * v.y - y * v.x; }

    float length() const { return sqrt(x * x + y * y); }

    Vec2 normalize() const {
        float l = length();
        return (l < 0.0001f) ? Vec2(0, 0) : Vec2(x / l, y / l);
    }
};

#endif
