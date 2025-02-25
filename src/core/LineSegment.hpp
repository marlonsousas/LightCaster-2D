#ifndef LINE_SEGMENT_HPP
#define LINE_SEGMENT_HPP

#include "Vec2.hpp"

struct LineSegment {
    Vec2 p1, p2;

    LineSegment(const Vec2& start, const Vec2& end) : p1(start), p2(end) {}

    bool intersect(const Ray& ray, float& t) const;
};

#endif
