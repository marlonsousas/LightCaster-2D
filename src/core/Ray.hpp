#ifndef RAY_HPP
#define RAY_HPP

#include "Vec2.hpp"

struct Ray {
    Vec2 origin;
    Vec2 direction;

    Ray(const Vec2& o, const Vec2& d) : origin(o), direction(d.normalize()) {}
};

#endif
